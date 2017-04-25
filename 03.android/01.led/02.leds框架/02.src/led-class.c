/*
 * LED Class Core
 *
 * Copyright (C) 2005 John Lenz <lenz@cs.wisc.edu>
 * Copyright (C) 2005-2007 Richard Purdie <rpurdie@openedhand.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/device.h>
#include <linux/timer.h>
#include <linux/err.h>
#include <linux/ctype.h>
#include <linux/leds.h>
#include "leds.h"

#define LED_BUFF_SIZE 50

static struct class *leds_class;

/*获取led亮度*/
static void led_update_brightness(struct led_classdev *led_cdev)
{
	if (led_cdev->brightness_get)
		led_cdev->brightness = led_cdev->brightness_get(led_cdev);
}

static ssize_t led_brightness_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);

	/* no lock needed for this */
	led_update_brightness(led_cdev);

	return snprintf(buf, LED_BUFF_SIZE, "%u\n", led_cdev->brightness);
}

static ssize_t led_brightness_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	unsigned long state;
	ssize_t ret = -EINVAL;

	ret = kstrtoul(buf, 10, &state);
	if (ret)
		return ret;

	led_cdev->usr_brightness_req = state;
	__led_set_brightness(led_cdev, state);

	return size;
}

static ssize_t led_max_brightness_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	ssize_t ret = -EINVAL;
	unsigned long state = 0;

	ret = strict_strtoul(buf, 10, &state);
	if (!ret) {
		ret = size;
		if (state > LED_FULL)
			state = LED_FULL;
		led_cdev->max_brightness = state;
		led_set_brightness(led_cdev, led_cdev->usr_brightness_req);
	}

	return ret;
}

static ssize_t led_max_brightness_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);

	return snprintf(buf, LED_BUFF_SIZE, "%u\n", led_cdev->max_brightness);
}

static struct device_attribute led_class_attrs[] = {
	__ATTR(brightness, 0644, led_brightness_show, led_brightness_store),//亮度节点
	__ATTR(max_brightness, 0644, led_max_brightness_show,  
			led_max_brightness_store),  //最大亮度节点
#ifdef CONFIG_LEDS_TRIGGERS
	__ATTR(trigger, 0644, led_trigger_show, led_trigger_store),//触发器
#endif
	__ATTR_NULL,
};

static void led_timer_function(unsigned long data)
{
	struct led_classdev *led_cdev = (void *)data;
	unsigned long brightness;
	unsigned long delay;

    /*led不闪烁*/
	if (!led_cdev->blink_delay_on || !led_cdev->blink_delay_off) {
		__led_set_brightness(led_cdev, LED_OFF);
		return;
	}

    /*关掉led一次性闪烁*/
	if (led_cdev->flags & LED_BLINK_ONESHOT_STOP) {
		led_cdev->flags &= ~LED_BLINK_ONESHOT_STOP;
		return;
	}

	brightness = led_get_brightness(led_cdev);
	if (!brightness) {//此时led灭,所有要选择亮led
		/* Time to switch the LED on. */
		brightness = led_cdev->blink_brightness;//亮度
		delay = led_cdev->blink_delay_on;//亮灯延时
	} else {//
		/* Store the current brightness value to be able
		 * to restore it when the delay_off period is over.
		 */
		led_cdev->blink_brightness = brightness;//保存当前亮度
		brightness = LED_OFF; //关led
		delay = led_cdev->blink_delay_off;//灭灯延时
	}

	__led_set_brightness(led_cdev, brightness);

	/* Return in next iteration if led is in one-shot mode and we are in
	 * the final blink state so that the led is toggled each delay_on +
	 * delay_off milliseconds in worst case.
	 */
    /*一次性闪烁控制,让下次定时器到来时，无法实现在此闪烁*/
	if (led_cdev->flags & LED_BLINK_ONESHOT) {
		if (led_cdev->flags & LED_BLINK_INVERT) {
			if (brightness)
				led_cdev->flags |= LED_BLINK_ONESHOT_STOP;
		} else {
			if (!brightness)
				led_cdev->flags |= LED_BLINK_ONESHOT_STOP;
		}
	}

    /*重新启动定时器*/
	mod_timer(&led_cdev->blink_timer, jiffies + msecs_to_jiffies(delay));
}

static void set_brightness_delayed(struct work_struct *ws)
{
	struct led_classdev *led_cdev =
		container_of(ws, struct led_classdev, set_brightness_work);

	led_stop_software_blink(led_cdev);//关闭led软件闪烁

	__led_set_brightness(led_cdev, led_cdev->delayed_set_value);
}

/**
 * led_classdev_suspend - suspend an led_classdev.
 *                        休眠一个led设备
 * @led_cdev: the led_classdev to suspend.
 */
void led_classdev_suspend(struct led_classdev *led_cdev)
{
	led_cdev->flags |= LED_SUSPENDED;
	led_cdev->brightness_set(led_cdev, 0);
}
EXPORT_SYMBOL_GPL(led_classdev_suspend);

/**
 * led_classdev_resume - resume an led_classdev.
 * @led_cdev: the led_classdev to resume.
 */
void led_classdev_resume(struct led_classdev *led_cdev)
{
	led_cdev->brightness_set(led_cdev, led_cdev->brightness);
	led_cdev->flags &= ~LED_SUSPENDED;
}
EXPORT_SYMBOL_GPL(led_classdev_resume);

static int led_suspend(struct device *dev, pm_message_t state)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);

	if (led_cdev->flags & LED_CORE_SUSPENDRESUME)
		led_classdev_suspend(led_cdev);//关闭相应led设备

	return 0;
}

static int led_resume(struct device *dev)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);

	if (led_cdev->flags & LED_CORE_SUSPENDRESUME)
		led_classdev_resume(led_cdev);//恢复led状态

	return 0;
}

/**
 * led_classdev_register - register a new object of led_classdev class.
 *                         注册一个led_classdev类的对象
 * @parent: The device to register.
 * @led_cdev: the led_classdev structure for this device.
 */
int led_classdev_register(struct device *parent, struct led_classdev *led_cdev)
{
    /*创建设备节点*/
	led_cdev->dev = device_create(leds_class, parent, 0, led_cdev,
				      "%s", led_cdev->name);
	if (IS_ERR(led_cdev->dev))
		return PTR_ERR(led_cdev->dev);

#ifdef CONFIG_LEDS_TRIGGERS
	init_rwsem(&led_cdev->trigger_lock);//创建触发器读写信号量锁
#endif
	/* add to the list of leds */
	down_write(&leds_list_lock);
	list_add_tail(&led_cdev->node, &leds_list); //将led设备添加到链表中
	up_write(&leds_list_lock);

	if (!led_cdev->max_brightness)
		led_cdev->max_brightness = LED_FULL;

	led_update_brightness(led_cdev);//更新led亮度

    /*创建工作队列*/
	INIT_WORK(&led_cdev->set_brightness_work, set_brightness_delayed);

	init_timer(&led_cdev->blink_timer);
	led_cdev->blink_timer.function = led_timer_function;
	led_cdev->blink_timer.data = (unsigned long)led_cdev;

#ifdef CONFIG_LEDS_TRIGGERS
	led_trigger_set_default(led_cdev);
#endif

	dev_dbg(parent, "Registered led device: %s\n",
			led_cdev->name);

	return 0;
}
EXPORT_SYMBOL_GPL(led_classdev_register);

/**
 * led_classdev_unregister - unregisters a object of led_properties class.
 *                           注销led属性类的对象
 * @led_cdev: the led device to unregister
 *
 * Unregisters a previously registered via led_classdev_register object.
 */
void led_classdev_unregister(struct led_classdev *led_cdev)
{
#ifdef CONFIG_LEDS_TRIGGERS
	down_write(&led_cdev->trigger_lock);
	if (led_cdev->trigger)
		led_trigger_set(led_cdev, NULL);
	up_write(&led_cdev->trigger_lock);
#endif

    /*删除工作队列*/
	cancel_work_sync(&led_cdev->set_brightness_work);

	/* Stop blinking */
    /*停止led闪烁*/
	led_stop_software_blink(led_cdev);
	led_set_brightness(led_cdev, LED_OFF);

    /*注销设备*/
	device_unregister(led_cdev->dev);

	down_write(&leds_list_lock);//上锁
	list_del(&led_cdev->node);  //删除链表中节点
	up_write(&leds_list_lock);  //下锁
}
EXPORT_SYMBOL_GPL(led_classdev_unregister);

static int __init leds_init(void)
{
    /*创建leds类*/
	leds_class = class_create(THIS_MODULE, "leds");
	if (IS_ERR(leds_class))
		return PTR_ERR(leds_class);
	leds_class->suspend = led_suspend;//休眠
	leds_class->resume = led_resume;  //唤醒
    /*brightness max_brightness trigger*/
	leds_class->dev_attrs = led_class_attrs;
	return 0;
}

static void __exit leds_exit(void)
{
	class_destroy(leds_class);//销毁leds类
}

subsys_initcall(leds_init);
module_exit(leds_exit);

MODULE_AUTHOR("John Lenz, Richard Purdie");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LED Class Interface");

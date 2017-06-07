#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>

irqreturn_t key_handler(int irqno, void *dev)
{
	printk("=====irqno====%d \n",irqno);
	return IRQ_HANDLED;
    irq_chip
}

static int hello_probe(struct platform_device *pdev)
{
	int ret;
	printk("match ok\n");
    /*注册中断*/
                        //中断号               中断处理函数 中断方式              中断名  共享中断
	ret = request_irq(pdev->resource[0].start, key_handler, IRQF_TRIGGER_FALLING, "KEY1",NULL);
	ret = request_irq(pdev->resource[1].start, key_handler, IRQF_TRIGGER_FALLING, "KEY2",NULL);

	return 0;
}
static int hello_remove(struct platform_device *pdev)
{
	return 0;
}
static struct of_device_id key_tbl[]={
	{.compatible = "fs4412,key"},
};

struct platform_driver pdrv={
	.probe = hello_probe,
	.remove = hello_remove,
	.driver= {
		.name = "fs4412-key",
		.of_match_table = key_tbl,
	},
};

int hello_init(void)
{
	printk("hello_init()\n");
	return platform_driver_register(&pdrv);
}
void hello_exit(void)
{
	platform_driver_unregister(&pdrv);
	return;
}

MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

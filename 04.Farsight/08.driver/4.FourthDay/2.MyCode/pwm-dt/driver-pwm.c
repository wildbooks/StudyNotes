#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <asm/io.h>
#include <linux/fs.h>

/* 
	beep  GPD0_0	XpwmTOUT0
	GPD0CON[3:0]=0x1
*/
#define TCFG0       0x0000
#define TCFG1       0x0004
#define TCON        0x0008
#define TCNTB0      0x000C
#define TCMPB0      0x0010
#define TCNTO0      0x0014

#define NS_IN_1HZ		(10000UL)
#define MAGIC_NUM 'J'
#define PWM_STOP 		_IO(MAGIC_NUM, 0)
#define PWM_SET_FRE 	_IO(MAGIC_NUM, 1)
/*
 *  TCNTB0	=	NS_IN_1HZ / freq 
 *	TCMPB0	=	NS_IN_1HZ / freq / 2
 */

static int major = 250;
static int minor = 0;
static dev_t devno;
static struct class *cls;
static struct device *tst_device;

static void *gpd0con;
static void *pwm_base;


static void fs4412_pwm_iounmap(void)
{
    iounmap(gpd0con);
    iounmap(pwm_base);
}

void fs4412_pwm_init(void)
{
	/*配置GPD0_0为TOUT_0输出*/
	writel((readl(gpd0con) & ~(0xf<<0)) | 0x2 <<0, gpd0con);

	/*配置PWM频率 */
	writel((readl(pwm_base + TCFG0) & ~(0xff<<0)) | 0xf9 <<0, pwm_base + TCFG0);
	writel((readl(pwm_base + TCFG1) & ~(0xf<<0)) | 0x2 << 0, pwm_base + TCFG1);
	/*配置占空比*/
#if 0
	writel(200,	pwm_base + TCNTB0);
	writel(100,	pwm_base + TCMPB0);

	/*先置位（manual update),再清除(置0) 数据才会被更新*/
	writel((readl(pwm_base + TCON) & ~(0xf<<0)) | 0x2 <<0, pwm_base + TCON);
#endif 
}



static int fs4412_pwm_open(struct inode *inode, struct file *file)
{
    printk("fs4412_pwm_open\n");
    return 0;
}
static int fs4412_pwm_release(struct inode *inode, struct file *file)
{
    printk("fs4412_pwm_release\n");
    return 0;
}

static void pwm_stop(void)
{
	/*TCON[0]=0*/
	writel(readl(pwm_base + TCON) & ~(0xf<<0), pwm_base + TCON);
	
}

static void pwm_start(void)
{
	/*TCON[0]=1	开启PWM*/
	/*先置位（manual update),再清除(置0) 数据才会被更新*/
	/* 此处必须完成(manual
	 * update)清空,否则数据不会被更新，蜂鸣器不会响*/
	writel((readl(pwm_base + TCON) & ~0xf) | (0x9<<0), pwm_base + TCON);
}

static void pwm_set_freq(unsigned long freq)
{
	int period_ns = NS_IN_1HZ / freq;
	/*改频率*/
	writel(period_ns, pwm_base + TCNTB0);
	writel(period_ns>>1, pwm_base + TCMPB0);
	writel((readl(pwm_base + TCON) & ~(0xf<<0)) | 0x2 <<0, pwm_base + TCON);

	/*开启pwm*/
	pwm_start();
}

static long fs4412_pwm_ioctl(struct file *filp, unsigned int cmd, \
		unsigned long arg)
{
	switch(cmd)
	{
	case PWM_SET_FRE:
		if(arg == 0)
			return -EINVAL;
		pwm_set_freq(arg);
		break;

	case PWM_STOP:
	default:
		pwm_stop();
		break;
	}
	return 0;
}

static struct file_operations fs4412_pwm_ops ={
    .owner			= THIS_MODULE,
    .open			= fs4412_pwm_open,        		//对应open();
    .release		= fs4412_pwm_release,    		//对应close();
    .unlocked_ioctl = fs4412_pwm_ioctl,		        //对应ioctl();
};

static int fs4412_pwm_platform_probe(struct platform_device *pdev)
{
    int ret;
    printk("match\n");

    /*1.注册设备号 和 字符设备  */
    ret = register_chrdev(major, "beep", &fs4412_pwm_ops);
    if(ret<0)
    {
        printk("fail \n");
        return ret;
    }
    /*2.自动创建设备节点*/
    cls = class_create(THIS_MODULE, "mycls");
    devno = MKDEV(major,minor);
    tst_device = device_create(cls, NULL, devno, NULL, "beep");

    /*3. 硬件初始化*/
    /*3.1 内存映射*/
    gpd0con = ioremap(pdev->resource[0].start, pdev->resource[0].end - pdev->resource[0].start);
    pwm_base = ioremap(pdev->resource[1].start, pdev->resource[1].end - pdev->resource[1].start);

    /*3.2 初始化pwm*/
    fs4412_pwm_init();
    return 0;
}

static int fs4412_pwm_platform_remove(struct platform_device *pdev)
{
    printk("remove\n");

    /*1. 取消内存映射*/
    fs4412_pwm_iounmap();
    /*2. 注销设备节点和类*/
    device_destroy(cls, devno);
    class_destroy(cls);

    /*3.注销字符设备*/
    unregister_chrdev(major, "beep");
    return 0;
}
static struct of_device_id fs4412_pwm_tbl[] ={
    {.compatible = "fs4412,beep"}
};

static struct platform_driver pdrv = {

    .probe          = fs4412_pwm_platform_probe,   //
    .remove         = fs4412_pwm_platform_remove,  //
    // void (*shutdown)(struct platform_device *);
    // int (*suspend)(struct platform_device *, pm_message_t state);
    // int (*resume)(struct platform_device *);
    // struct device_driver driver;
    .driver.name    = "pwm_device",    //设备名 驱动和设备通过它识别
    .driver.of_match_table = fs4412_pwm_tbl,
    // const struct platform_device_id *id_table;
    // bool prevent_deferred_probe;
};


static int fs4412_pwm_platform_driver_init(void)
{

    printk("fs4412_pwm_platform_driver_init()\n");
    return platform_driver_register(&pdrv);
}
static void fs4412_pwm_platform_driver_exit(void)
{
    printk("fs4412_pwm_platform_driver_exit()\n");
    platform_driver_register(&pdrv);
    return;
}
MODULE_LICENSE("GPL");
module_init(fs4412_pwm_platform_driver_init);
module_exit(fs4412_pwm_platform_driver_exit);




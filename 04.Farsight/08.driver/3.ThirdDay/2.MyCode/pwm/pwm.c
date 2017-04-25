#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>

/*
	beep  GPD0_0	XpwmTOUT0
	GPD0CON[3:0]=0x1
*/



#define MAGIC_NUM 'J'
#define PWM_STOP 		_IO(MAGIC_NUM, 0)
#define PWM_SET_FRE 	_IO(MAGIC_NUM, 1)
#define DEVICE "pwm"


#define GPD0CON		0x114000A0
#define PWM_BASE	0x139D0000

#define TCFG0		0x0000
#define TCFG1		0x0004
#define TCON		0x0008
#define TCNTB0		0x000C
#define TCMPB0		0x0010
#define TCNTO0		0x0014


#define NS_IN_1HZ		(10000UL)
/*
 *  TCNTB0	=	NS_IN_1HZ / freq
 *	TCMPB0	=	NS_IN_1HZ / freq / 2
 */


static int major = 250;
static int minor = 0;
static dev_t devno;
static struct class *cls;
static struct device *tst_device;
void  *pwm_base;
void  *gpd0con;

void pwm_ioremap(void)
{
	gpd0con = ioremap(GPD0CON, 4);
	pwm_base = ioremap(PWM_BASE, 0x14);
}
void pwm_iounmap(void)
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

static int fs4412_pwm_open(struct inode *inode, struct file *file)
{
	printk("hello_open\n");

	return 0;
}
static int fs4412_pwm_release(struct inode *inode, struct file *file)
{
	printk("hello_release\n");

	return 0;
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

struct file_operations hello_ops ={
	.owner			= THIS_MODULE,
	.open			= fs4412_pwm_open,        		//对应open();
	.release		= fs4412_pwm_release,    		//对应close();
	.unlocked_ioctl = fs4412_pwm_ioctl,				//对应ioctl();
};

static int fs4412_pwm_dev_init(void)
{
	int ret;

	printk("pwm_dev_init()\n");
	ret = register_chrdev(major, DEVICE, &hello_ops);
	if(ret<0)
	{
		printk("fail \n");
		return ret;
	}
	cls = class_create(THIS_MODULE, "ledcls");
	devno = MKDEV(major,minor);
	tst_device = device_create(cls, NULL, devno, NULL, DEVICE);
	pwm_ioremap();
	fs4412_pwm_init();
	return 0;
}


static void fs4412_pwm_dev_exit(void)
{
	printk("pwm_dev_exit()\n");
	pwm_iounmap();
	device_destroy(cls, devno);
	class_destroy(cls);

	unregister_chrdev(major, DEVICE);
	return;
}
MODULE_LICENSE("GPL");
module_init(fs4412_pwm_dev_init);
module_exit(fs4412_pwm_dev_exit);




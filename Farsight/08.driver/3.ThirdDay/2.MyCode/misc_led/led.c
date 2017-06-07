#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>
#include <linux/miscdevice.h>

/*
	1.LED2 -- LED5
	GPX2_7 GPX1_0	GPF3_4	GPF3_5
*/


#define DEVICE_NAME "leds"

#define GPX2CON   	0x11000C40
#define GPX2DAT 	0x11000C44
#define GPX1CON   	0x11000C20
#define GPX1DAT    	0x11000C24
#define GPF3CON  	0x114001E0
#define GPF3DAT   	0x114001E4

void * pgpx2con;
void * pgpx2dat;
void * pgpx1con;
void * pgpx1dat;
void * pgpf3con;
void * pgpf3dat;


static void led_ioremap(void)
{
	pgpx2con = ioremap(GPX2CON, 4);
	pgpx2dat = ioremap(GPX2DAT, 4);
	pgpx1con = ioremap(GPX1CON, 4);
	pgpx1dat = ioremap(GPX1DAT, 4);
	pgpf3con = ioremap(GPF3CON, 4);
	pgpf3dat = ioremap(GPF3DAT, 4);
}
static void led_iounmap(void)
{
	iounmap(pgpx2con);
	iounmap(pgpx2dat);
	iounmap(pgpx1con);
	iounmap(pgpx1dat);
	iounmap(pgpf3con);
	iounmap(pgpf3dat);
}

static void fs4412_led_init(void)
{
	writel((readl(pgpx2con) & ~(0xf<<28)) | 0x1 <<28,pgpx2con);
	writel((readl(pgpx1con) & ~(0xf<<0)) | 0x1 <<0,pgpx1con);
	writel((readl(pgpf3con) & ~(0xff<<16)) | 0x11 <<16,pgpf3con);
}


/*
	1.LED2 -- LED5
	GPX2_7 GPX1_0	GPF3_4	GPF3_5
*/


static long fs4412led_cmd(unsigned int ledno, unsigned long cmd)
{
	switch(ledno)
	{
		case 1:	//7=ledno+6=1+6
			writel((readl(pgpx2dat) & ~(1 << 7)) | (cmd << 7), pgpx2dat);
			break;
		case 2:
			writel((readl(pgpx1dat) & ~(1 << 0)) | (cmd << 0), pgpx1dat);
			break;
		case 3:	//4=3+1=ledno+1
		case 4:	//5=4+1=ledno+1
			writel((readl(pgpf3dat) & ~(1 << (ledno + 1))) | (cmd << (ledno + 1)),pgpf3dat);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}

static void fs4412_leds_OFFALL(void)
{
	fs4412led_cmd(1, 0);
	fs4412led_cmd(2, 0);
	fs4412led_cmd(3, 0);
	fs4412led_cmd(4, 0);
}

static void fs4412_leds_ONALL(void)
{
	fs4412led_cmd(1, 1);
	fs4412led_cmd(2, 1);
	fs4412led_cmd(3, 1);
	fs4412led_cmd(4, 1);
}


static int fs4412_leds_open(struct inode *inode, struct file *file)
{
	printk("fs4412_leds_open\n");
	fs4412_leds_ONALL();

	return 0;
}
static int fs4412_leds_release(struct inode *inode, struct file *file)
{
	printk("fs4412_leds_release\n");
	fs4412_leds_OFFALL();

	return 0;
}


//GPX2_7 GPX1_0	GPF3_4	GPF3_5
static long fs4412_leds_ioctl(struct file *filp, unsigned int ledno, unsigned long cmd)
{
	 //参数2传递不进去,用5替代
	if(ledno == 5)
		ledno = 2;
	switch(ledno)
	{
	case 0:
	case 1:
		fs4412led_cmd(ledno, cmd);
		break;
	default:
		return -EINVAL;

	}
}

struct file_operations fs4412_leds_dev_fops ={
	.owner			= THIS_MODULE,
	.open			= fs4412_leds_open,        		//对应open();
	.release		= fs4412_leds_release,    		//对应close();
	.unlocked_ioctl = fs4412_leds_ioctl,			//对应ioctl();
};


static struct miscdevice fs4412_leds_dev = {
	.minor 			= MISC_DYNAMIC_MINOR,
	.name			= DEVICE_NAME,
	.fops			= &fs4412_leds_dev_fops,
};

static int __init fs4412_leds_dev_init(void)
{
	int ret;

	printk("fs4412_leds_init()\n");
	/*1.注册混杂设备 */
	//自动创建设备节点，是主设备号为10
	ret = misc_register(&fs4412_leds_dev);

    cls = class_create(THIS_MODULE, "ledcls");

	led_ioremap();
	fs4412_led_init();
	return ret;
}
static void __exit fs4412_leds_dev_exit(void)
{
	printk("fs4412_leds_exit()\n");
	/*1.注册混杂设备 */
	//在卸载模块时,会自动删除设备文件
	misc_deregister(&fs4412_leds_dev);
	led_iounmap();

}
MODULE_LICENSE("GPL");
module_init(fs4412_leds_dev_init);
module_exit(fs4412_leds_dev_exit);




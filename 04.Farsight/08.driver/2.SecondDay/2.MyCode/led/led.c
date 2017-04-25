#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>

/* 
	1.LED2 -- LED5
	GPX2_7 GPX1_0	GPF3_4	GPF3_5
*/


static int major = 250;
static int minor = 0;
static dev_t devno;
static  struct cdev cdev;
static struct class *cls;
static struct device *tst_device;


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


void led_ioremap(void)
{
	pgpx2con = ioremap(GPX2CON, 4);
	pgpx2dat = ioremap(GPX2DAT, 4);
	pgpx1con = ioremap(GPX1CON, 4);
	pgpx1dat = ioremap(GPX1DAT, 4);
	pgpf3con = ioremap(GPF3CON, 4);
	pgpf3dat = ioremap(GPF3DAT, 4);	
}
void led_iounmap(void)
{
	iounmap(pgpx2con);
	iounmap(pgpx2dat);
	iounmap(pgpx1con);
	iounmap(pgpx1dat);
	iounmap(pgpf3con);
	iounmap(pgpf3dat);
}

void fs4412_led_init(void)
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
			writel(readl(pgpx2dat) & ~(1 << 7) | (cmd << 7), pgpx2dat);
			break;
		case 2:
			writel(readl(pgpx1dat) & ~(1 << 0) | (cmd << 0), pgpx1dat);
			break;
		case 3:	//4=3+1=ledno+1
		case 4:	//5=4+1=ledno+1
			writel(readl(pgpf3dat) & ~(1 << (ledno + 1)) | (cmd << (ledno + 1)),pgpf3dat);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}


static int hello_open(struct inode *inode, struct file *file)
{
	printk("hello_open\n");

#if 1
	fs4412led_cmd(1, 1);
	fs4412led_cmd(2, 1);
	fs4412led_cmd(3, 1);
	fs4412led_cmd(4, 1);
#endif 
	return 0;
}
static int hello_release(struct inode *inode, struct file *file)
{
	printk("hello_release\n");
#if 1
	fs4412led_cmd(1, 0);
	fs4412led_cmd(2, 0);
	fs4412led_cmd(3, 0);
	fs4412led_cmd(4, 0);
#endif
	return 0;
}


//GPX2_7 GPX1_0	GPF3_4	GPF3_5
static long fs4412_leds_ioctl(struct file *filp, unsigned int ledno, unsigned long cmd)
{
	switch(ledno)
	{
		case 1:	//7=ledno+6=1+6
			writel(readl(pgpx2dat) & ~(1 << 7) | (cmd << 7), pgpx2dat);
			break;
		case 2:
			writel(readl(pgpx1dat) & ~(1 << 0) | (cmd << 0), pgpx1dat);
			break;
		case 3:	//4=3+1=ledno+1
		case 4:	//5=4+1=ledno+1
			writel(readl(pgpf3dat) & ~(1 << (ledno + 1)) | (cmd << (ledno + 1)),pgpf3dat);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}

struct file_operations hello_ops ={
	.owner			= THIS_MODULE,
	.open			= hello_open,        		//对应open();
	.release		= hello_release,    		//对应close();
	.unlocked_ioctl = fs4412_leds_ioctl,		//对应ioctl();
};

static int hello_init(void)
{
	int ret;
	
	printk("hello_init()\n");
	ret = register_chrdev(major, "led", &hello_ops);
	if(ret<0)
	{	
		printk("fail \n");
		return ret;		
	}
	cls = class_create(THIS_MODULE, "mycls");
	devno = MKDEV(major,minor);
	tst_device = device_create(cls, NULL, devno, NULL, "led");
	led_ioremap();
	fs4412_led_init();
	return 0;
}
static void hello_exit(void)
{
	printk("hello_exit()\n");
	led_iounmap();
	device_destroy(cls, devno);
	class_destroy(cls);
	
	unregister_chrdev(major, "led");
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);




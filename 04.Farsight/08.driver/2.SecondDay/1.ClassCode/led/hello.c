#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>

static int major = 250;
static int minor = 0;
static dev_t devno;
static  struct cdev cdev;
static struct class *cls;
static struct device *tst_device;



#define GPX2CON   0x11000C40
#define GPX2DAT    0x11000C44
#define GPX1CON   0x11000C20
#define GPX1DAT    0x11000C24
#define GPF3CON  0x114001E0 
#define GPF3DAT   0x114001E4 

void * pgpx2con;
void * pgpx2dat;
void * pgpx1con;
void * pgpx1dat;
void * pgpf3con;
void * pgpf3dat;


void led_ioremap(void)
{
	pgpx2con = ioremap( GPX2CON  ,4);
	pgpx2dat = ioremap( GPX2DAT,4);
	pgpx1con = ioremap( GPX1CON ,4);
	pgpx1dat = ioremap( GPX1DAT ,4);
	pgpf3con = ioremap(  GPF3CON ,4);
	pgpf3dat = ioremap(  GPF3DAT,4);	
}
void led_iounmap(void)
{
	iounmap(   pgpx2con           );
	iounmap(   pgpx2dat           );
	iounmap(   pgpx1con           );
	iounmap(   pgpx1dat           );
	iounmap(   pgpf3con            );
	iounmap(   pgpf3dat            );
}

void fs4412_led_init(void)
{	
	writel((readl(pgpx2con) & ~(0xf<<28)) | 0x1 <<28,pgpx2con);
	writel((readl(pgpx1con) & ~(0xf<<0)) | 0x1 <<0,pgpx1con);
	writel((readl(pgpf3con) & ~(0xff<<16)) | 0x11 <<16,pgpf3con);	
}
void fs4412led_on(int ledno)
{
	switch(ledno)
	{
		case 1:
			writel(readl(pgpx2dat) | 1<<7,pgpx2dat);
			break;
		case 2:
			writel(readl(pgpx1dat) | 1<<0,pgpx1dat);
			break;
		case 3:
			writel(readl(pgpf3dat) | 1<<4,pgpf3dat);
			break;
		case 4:
			writel(readl(pgpf3dat) | 1<<5,pgpf3dat);
			break;
		default:
			break;
	}
}
void fs4412led_off(int ledno)
{
	switch(ledno)
	{
		case 1:
			writel(readl(pgpx2dat) & ~( 1<<7),pgpx2dat);
			break;
		case 2:
			writel(readl(pgpx1dat) &~( 1<<0),pgpx1dat);
			break;
		case 3:
			writel(readl(pgpf3dat) &~( 1<<4),pgpf3dat);
			break;
		case 4:
			writel(readl(pgpf3dat) &~( 1<<5),pgpf3dat);
			break;
		default:
			break;
	}
}
static int hello_open(struct inode *inode, struct file *file)
{
	printk("hello_open\n");
	fs4412led_on(1);
	fs4412led_on(2);
	fs4412led_on(3);
	fs4412led_on(4);
	return 0;
}
static int hello_release(struct inode *inode, struct file *file)
{
	printk("hello_release\n");
	fs4412led_off(1);
	fs4412led_off(2);
	fs4412led_off(3);
	fs4412led_off(4);
	return 0;
}

struct file_operations hello_ops ={
	.owner		= THIS_MODULE,
	.open		= hello_open,        //open();
	.release	       = hello_release,    //close();
};

static int hello_init(void)
{
	int ret,rc;
	
	printk("hello_init()\n");
	ret = register_chrdev(major, "hello", &hello_ops);
	if(ret<0)
	{	
		printk("fail \n");
		return ret;		
	}
	cls = class_create(THIS_MODULE, "mycls");
	devno = MKDEV(major,minor);
	tst_device = device_create(cls, NULL, devno, NULL, "hello");
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
	
	unregister_chrdev(major, "hello");
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

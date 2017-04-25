#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>
#include <asm/uaccess.h>


static int major = 250;
static int minor = 0;
static dev_t devno;
static  struct cdev cdev;
static struct class *cls;
static struct device *tst_device;

#define GPD0CON       0x114000a0
#define FS4412TIMER_BASE	0x139D0000


#define TCFG0 0x0000   
#define TCFG1 0x0004   
#define TCON 0x0008    
#define TCNTB0 0x000C 
#define TCMPB0 0x0010 

static void *pgpd0con;
static void *timerbase;

void fs4412beep_on(void)
{
	writel((readl(timerbase +TCON )&~(0xf<<0))|0x9,timerbase +TCON);
}
void fs4412beep_off(void)
{
	writel((readl(timerbase +TCON )&~(0xf<<0))|0,timerbase +TCON);
}

void fs4412beep_init(void)
{
	writel((readl(pgpd0con)& ~(0xf<<0)) |(0x2<<0)   ,pgpd0con);
	writel((readl(timerbase +TCFG0 )&~(0xff<<0))|(0xff<<0),timerbase +TCFG0);
	writel((readl(timerbase +TCFG1 )&~(0xf<<0))|(0x3<<0),timerbase +TCFG1);	

	writel(200,timerbase + TCNTB0);
	writel(100,timerbase + TCMPB0);

	writel((readl(timerbase +TCON )&~(0xf<<0))|(0x1<<1),timerbase +TCON);
	
}


void fs4412beep_ioremap(void)
{
	pgpd0con = ioremap(GPD0CON,4);
	timerbase = ioremap(FS4412TIMER_BASE,0X14);
}
void fs4412beep_iounmap(void)
{
	iounmap(pgpd0con);
	iounmap(timerbase);
}
static int hello_open(struct inode *inode, struct file *file)
{
	printk("hello_open\n");
	fs4412beep_on();
	return 0;
}
static int hello_release(struct inode *inode, struct file *file)
{
	printk("hello_release\n");
	fs4412beep_off();
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
	fs4412beep_ioremap();
	fs4412beep_init();
	return 0;
}
static void hello_exit(void)
{
	printk("hello_exit()\n");
	fs4412beep_iounmap();
	device_destroy(cls, devno);
	class_destroy(cls);
	
	unregister_chrdev(major, "hello");
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

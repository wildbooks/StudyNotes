#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

static int major = 240;
static int minor = 0;
static dev_t devno;
#define DEVRICE "hello"
static struct class *cls;
static struct device *tst_device;

struct semaphore sem;

static int hello_open(struct inode *inode, struct file *file)
{
	printk("open success\n");
	if(down_interruptible(&sem))
		return -ERESTARTSYS;

	//down(&sem);
	return 0;
}
static int hello_release(struct inode *inode, struct file *file)
{
	printk("hello_release\n");

	up(&sem);
	return 0;
}

struct file_operations hello_ops ={
	.owner		= THIS_MODULE,
	.open		= hello_open,        	//open();
	.release	= hello_release,    	//close();
};

static int hello_init(void)
{
	int ret;
	
	printk("hello_init()\n");
	ret = register_chrdev(major, DEVRICE, &hello_ops);
	{	
		printk("fail \n");
		return ret;		
	}

	/*2. 自动创建设备节点*/
	/*2.1. 创建一个类*/
	cls = class_create(THIS_MODULE, "mycls");
	devno = MKDEV(major,minor);
	/*2.2. 创建设备节点*/
	tst_device = device_create(cls, NULL, devno, NULL, DEVRICE);

	/*信号量*/
	sema_init(&sem, 1);
	return 0;
}
static void hello_exit(void)
{
	printk("hello_exit()\n");

	/*1. 自动卸载设备节点*/
	/*1.1 释放设备*/
	device_destroy(cls, devno);
	/*1.2 释放类*/
	class_destroy(cls);
	
	/*释放设备号*/
	unregister_chrdev(major, DEVRICE);
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

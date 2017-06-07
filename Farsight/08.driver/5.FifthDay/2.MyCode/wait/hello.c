#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/wait.h>
#include <asm/uaccess.h>

static int major = 240;
static int minor = 0;
static dev_t devno;
#define DEVRICE "hello"
static struct class *cls;
static struct device *tst_device;
static wait_queue_head_t wq;
static int have_data = 0;

static int hello_open(struct inode *inode, struct file *file)
{
	printk("open success\n");

	return 0;
}
static int hello_release(struct inode *inode, struct file *file)
{
	printk("hello_release\n");

	return 0;
}

static char kbuf[64] = "kernel\n";
ssize_t hello_read(struct file *filep, char __user *buf, size_t size, loff_t *pos)
{
	if(size > 64)
	{
		size = 64;	
	}
			
	wait_event_interruptible(wq, have_data == 1);
	if(copy_to_user(buf, kbuf, size))
	{
		return	-EFAULT;	
	}
	have_data = 0;	//读走数据修改该值表示数据为空
	return size;
}
ssize_t hello_write(struct file *filep, const char __user *buf, size_t size, loff_t *pos)
{
	if(size > 64)
	{
		size = 64;	
	}
	if(copy_from_user(buf, kbuf, size))
	{
		return	-EFAULT;	
	}
	have_data = 1;	//表示有数据
	wake_up_interruptible(&wq);	//
	return size;
}
struct file_operations hello_ops ={
	.owner		= THIS_MODULE,
	.open		= hello_open,        	//open();
	.release	= hello_release,    	//close();
	.read		= hello_read,
	.write		= hello_write,
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

	init_waitqueue_head(&wq);
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

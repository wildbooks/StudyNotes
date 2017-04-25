#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

static int major = 240;
static int minor = 0;
static dev_t devno;
static struct class *cls;
static struct device *tst_device;



static wait_queue_head_t wq;
static int hello_open(struct inode *inode, struct file *file)
{
	printk("hello_open\n");

	return 0;	
}
static int hello_release(struct inode *inode, struct file *file)
{
	printk("hello_release\n");

	return 0;
}
static int have_data =0;
static char kbuf[64]="kernel\n";
ssize_t hello_read(struct file *filep, char __user *buf, size_t size, loff_t *pos)
{
	if(size>64)
	{
		size = 64;
	}

	//当被wake_up，且条件(have_data==1)成立，会退出休眠状态
	wait_event_interruptible(wq, have_data==1);			//阻塞
	if(copy_to_user(buf,kbuf,size))
	{
		return -EFAULT;
	}
	have_data = 0;//读走数据修改该值表示数据为空
	return size;
}
ssize_t hello_write(struct file *filep, const char __user *buf, size_t size, loff_t *pos)
{
	if(size>64)
	{
		size = 64;
	}

	if(copy_from_user(kbuf,buf,size))
	{
		return -EFAULT;
	}
	have_data = 1;//表示有数据
	wake_up_interruptible(&wq);	//唤醒
	return size;
}

struct file_operations hello_ops ={
	.owner		= THIS_MODULE,
	.open		= hello_open,  		//open();
	.release	= hello_release,	//close();
	.read		= hello_read,
	.write		= hello_write,
};

static int hello_init(void)
{
	int ret;
	
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

	init_waitqueue_head(&wq);
	return 0;
}
static void hello_exit(void)
{
	printk("hello_exit()\n");
	device_destroy(cls, devno);
	class_destroy(cls);
	
	unregister_chrdev(major, "hello");
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

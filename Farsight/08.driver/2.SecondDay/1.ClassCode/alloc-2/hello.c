#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

static int major = 250;
static int minor = 0;
static dev_t devno;
static  struct cdev cdev;

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

struct file_operations hello_ops ={
	.owner		= THIS_MODULE,
	.open		= hello_open,        		//open();
	.release	       = hello_release,    	//close();
};

static int hello_init(void)
{
	int ret;
	
	printk("hello_init()\n");

	/*1. 自动注册设备号和设备*/
	/* 
	 *	包含以下功能
	 *		1. 注册设备号
	 *			1) 手动注册设备
	 *				1》手动申请设备号
	 *				2》注册设备号
	 *			1) 自动注册设备
	 *		2. 初始化设备
	 *		3. 注册设备
	 *	注意事项：
	 *		主设备号
	 *		major = 0,动态分配设备号，返回主设备号
	 *		major > 0 尝试申请，
	 */
	ret = register_chrdev(major, "hello", &hello_ops);
	if(ret<0)
	{	
		printk("fail \n");
		return ret;		
	}

	/*2. 自动创建设备节点*/
	
	/*3. 硬件初始化*/
	return 0;
}


static void hello_exit(void)
{
	printk("hello_exit()\n");

	/*自动释放设备号和设备*/
	unregister_chrdev(major, "hello");
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

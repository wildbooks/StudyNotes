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
	.open		= hello_open,        //open();
	.release	       = hello_release,    //close();
};

static int hello_init(void)
{
	int ret;
	
	printk("hello_init()\n");

	/*1. 手动创建设备号*/
	devno = MKDEV(major,minor);

	/*2. 注册设备号*/
	ret = register_chrdev_region(devno, 1, "hello");
	if(ret<0)
	{
		printk("fail \n");
		return ret;
	}

	/*3. 字符设备初始化 */
	cdev_init(&cdev, &hello_ops);

	/*4. 注册字符设备*/
	ret = cdev_add(&cdev, devno, 1);
	if(ret<0)
	{
		unregister_chrdev_region(devno, 1);
		return ret;
	}
	
	/*5. 自动创建设备节点*/

	/*6. 初始化硬件*/

	return 0;
}
static void hello_exit(void)
{
	printk("hello_exit()\n");

	/*1. 释放设备节点*/

	/*2. 释放设备*/
	cdev_del(&cdev);

	/*3. 释放设备号*/
	unregister_chrdev_region(devno, 1);
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

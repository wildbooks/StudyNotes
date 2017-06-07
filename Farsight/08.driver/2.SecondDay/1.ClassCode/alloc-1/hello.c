#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

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
    .release	       = hello_release,    //close();
};

static int hello_init(void)
{
    int ret;

    printk("hello_init()\n");

    /*1. 动态注册设备号*/
    ret = alloc_chrdev_region(&devno, 0, 1, "hello");
    if(ret<0)
    {
        printk("fail \n");
        return ret;
    }

    /*2. 字符设备初始化 */
    cdev_init(&cdev, &hello_ops);

    /*3. 注册字符设备*/
    ret = cdev_add(&cdev, devno, 1);
    if(ret<0)
    {
        unregister_chrdev_region(devno, 1);
        return ret;
    }
    /*4. 自动创建设备节点*/

    /*5. 初始化硬件*/

    return ret;
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

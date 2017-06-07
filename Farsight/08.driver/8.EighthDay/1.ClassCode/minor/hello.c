#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

static int major = 240;
static int minor = 0;
static dev_t devno;
static struct class *cls;
static struct device *tst_device;


static unsigned int minorled;

ssize_t hello_read(struct file *file, char __user *buf, size_t size, loff_t *pos)
{
    minorled  = *(unsigned int*)(file->private_data);

    printk("hello_read : minor = %d \n",minorled);

    if(copy_to_user(buf,&minorled,size))
    {
        return -EFAULT;
    }

    return size;

}
static int hello_open(struct inode *inode, struct file *file)
{
    printk("hello_open\n");

    minorled =MINOR(inode->i_rdev);
    file->private_data = &minorled ;
    return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
    printk("hello_release\n");
    return 0;
}

struct file_operations hello_ops ={
    .owner		= THIS_MODULE,
    .open		= hello_open,               //open();
    .release    = hello_release,            //close();
    .read       = hello_read,
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

    /*自动创建设备节点*/
    cls = class_create(THIS_MODULE, "mycls");
    devno = MKDEV(major,minor);
    tst_device = device_create(cls, NULL, devno, NULL, "hello");

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

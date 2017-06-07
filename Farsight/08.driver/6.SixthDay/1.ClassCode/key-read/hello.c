#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/sched.h>

static  int major = 250;

wait_queue_head_t wq;
static int have_data = 0;

static int keyno;
struct resource * res1;
struct resource * res2;

ssize_t hello_read(struct file *file, char __user *buf, size_t size, loff_t *pos)
{
	if(size!=4)
	{
		size = 4;
	}
	wait_event_interruptible(wq, have_data==1);
	if(copy_to_user(buf,&keyno,size))
	{
		return -EFAULT;
	}
	have_data =0;
	return size;
}

irqreturn_t key_handler(int irqno, void *dev)
{
	printk("=====irqno====%d \n",irqno);

	if(irqno  == res1->start)
	{
		keyno = 1;
	}
	if( irqno == res2->start)
	{
		keyno = 2;
	}
	have_data = 1;

	wake_up(&wq);

	return IRQ_HANDLED;
}

int hello_open(struct inode *inode, struct file *file)
{
	return 0;
}

int hello_release(struct inode *inode, struct file *file)
{
	return 0;
}


struct file_operations fops={
	.open = hello_open,
	.release = hello_release,
	.read = hello_read,
 };

static int hello_probe(struct platform_device *pdev)
{
	int ret;
	printk("match ok\n");

    /*从pdev中获取资源 资源类型 第几个资源（0开始编号）*/
	res1 = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	res2 = platform_get_resource(pdev, IORESOURCE_IRQ, 1);

	ret = request_irq(res1->start, key_handler, IRQF_TRIGGER_FALLING, "KEY1",NULL);
	ret = request_irq(res2->start, key_handler, IRQF_TRIGGER_FALLING, "KEY2",NULL);

	register_chrdev(major, "key", &fops);

	init_waitqueue_head(&wq);
	return 0;
}
static int hello_remove(struct platform_device *pdev)
{
	/*注销中断号*/
	free_irq(res1->start, NULL);
	free_irq(res2->start, NULL);
	unregister_chrdev(major, "key");
	return 0;
}
static struct of_device_id key_tbl[]={
	{.compatible = "fs4412,key"},
};

struct platform_driver pdrv={
	.probe = hello_probe,
	.remove = hello_remove,
	.driver= {
		.name = "fs4412-key",
		.of_match_table = key_tbl,
	},
};

int hello_init(void)
{
	printk("hello_init()\n");
	return platform_driver_register(&pdrv);
}
void hello_exit(void)
{
	platform_driver_unregister(&pdrv);
	return;
}

MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

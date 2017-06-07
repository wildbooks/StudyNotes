#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>
#include <asm/io.h>
#include <linux/fs.h>
#include <linux/sched.h>

static  int major = 250;

wait_queue_head_t wq;
static int have_data = 0;

static int adcno;
struct resource * res1;
struct resource * res2;
static void *adc_base;

#define ADCCON 0x0000
#define ADCDAT 0x000C
#define CLRINTADC 0x0018
#define ADCMUX 0x001C

wait_queue_head_t wq;
static int havedata=0;

int hello_open(struct inode *inode, struct file *file)
{
	return 0;
}

int hello_release(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t hello_read (struct file *file, char __user *buf, size_t size, loff_t *pos)
{
	int adc ;
	if(size !=4)
	{
		size = 4;
	}

	writel(3,adc_base + ADCMUX);
	writel(1<<16 | 1<<14 | 0xff<<6 |  1<<0 ,adc_base + ADCCON);

	wait_event_interruptible(wq, havedata == 1);
	adc = readl(adc_base  + ADCDAT)&0xfff ;
	if(copy_to_user(buf,&adc,size))
	{
		return -EFAULT;
	}
	return size;
}
 struct file_operations fops={
	.open    = hello_open,
	.release = hello_release,
	.read     = hello_read,
 };


 irqreturn_t adc_handler(int irqno, void *dev)
 {
	printk("==%d ===\n",irqno);
	havedata = 1;
	wake_up(&wq);
	writel(12,adc_base  +CLRINTADC );//清中断
	return IRQ_HANDLED;
 }
static int hello_probe(struct platform_device *pdev)
{
	int ret;
	printk("match ok\n");
	res1 = platform_get_resource(pdev,IORESOURCE_MEM, 0);
	res2 = platform_get_resource(pdev,IORESOURCE_IRQ, 0);

	adc_base = ioremap(res1->start, res1->end - res1->start);
	ret = request_irq(res2->start, adc_handler, res2->flags,"adc", NULL);

    //申请设备号 初始化设备 注册设备
	register_chrdev(major, "adc", &fops);
	init_waitqueue_head(&wq);
	return 0;
}
static int hello_remove(struct platform_device *pdev)
{
	free_irq(res2->start,NULL);
	iounmap(adc_base);
	unregister_chrdev(major, "adc");
	return 0;
}
static struct of_device_id adc_tbl[]={
	{.compatible = "fs4412,adc"},
};

struct platform_driver pdrv={
	.probe = hello_probe,
	.remove = hello_remove,
	.driver= {
		.name = "fs4412-adc",
		.of_match_table = adc_tbl,
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

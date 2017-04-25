#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <asm/io.h>
#include <linux/fs.h>

/* 
	1.LED2 -- LED5
	GPX2_7 GPX1_0	GPF3_4	GPF3_5
*/

static int major = 250;
static int minor = 0;
static dev_t devno;
static struct class *cls;
static struct device *tst_device;

static void * pgpx2con;
static void * pgpx1con;
static void * pgpf3con;
#define DAT         0x4     //偏移量


static void fs4412_leds_iounmap(void)
{
	iounmap(pgpx2con);
	iounmap(pgpx1con);
	iounmap(pgpf3con);
}

static void fs4412_leds_init(void)
{
	writel((readl(pgpx2con) & ~(0xf<<28)) | 0x1 <<28,pgpx2con);
	writel((readl(pgpx1con) & ~(0xf<<0)) | 0x1 <<0,pgpx1con);
	writel((readl(pgpf3con) & ~(0xff<<16)) | 0x11 <<16,pgpf3con);
}


/*
	1.LED2 -- LED5
	GPX2_7 GPX1_0	GPF3_4	GPF3_5
*/


static long fs4412_leds_cmd(unsigned int ledno, unsigned long cmd)
{
	switch(ledno)
	{
		case 1:	//7=ledno+6=1+6
			writel((readl(pgpx2con + DAT) & ~(1 << 7)) | (cmd << 7), pgpx2con +DAT);
			break;
		case 2:
			writel((readl(pgpx1con + DAT) & ~(1 << 0)) | (cmd << 0), pgpx1con + DAT);
			break;
		case 3:	//4=3+1=ledno+1
		case 4:	//5=4+1=ledno+1
			writel((readl(pgpf3con + DAT) & ~(1 << (ledno + 1))) | (cmd << (ledno + 1)),pgpf3con + DAT);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}

static int fs4412_leds_open(struct inode *inode, struct file *file)
{
	printk("fs4412_leds_open\n");

	fs4412_leds_cmd(1, 1);
	fs4412_leds_cmd(2, 1);
	fs4412_leds_cmd(3, 1);
	fs4412_leds_cmd(4, 1);
	return 0;
}
static int fs4412_leds_release(struct inode *inode, struct file *file)
{
	printk("fs4412_leds_release\n");
	fs4412_leds_cmd(1, 0);
	fs4412_leds_cmd(2, 0);
	fs4412_leds_cmd(3, 0);
	fs4412_leds_cmd(4, 0);
	return 0;
}

//GPX2_7 GPX1_0	GPF3_4	GPF3_5
static long fs4412_leds_ioctl(struct file *filp, unsigned int ledno, unsigned long cmd)
{
	switch(ledno)
	{
		case 1:	//7=ledno+6=1+6
			writel((readl(pgpx2con + DAT) & ~(1 << 7)) | (cmd << 7), pgpx2con + DAT);
			break;
		//case 2:	参数2传递不进去,用5替代
		case 5:

			writel((readl(pgpx1con + DAT) & ~(1 << 0)) | (cmd << 0), pgpx1con + DAT);
			break;
		case 3:	//4=3+1=ledno+1
		case 4:	//5=4+1=ledno+1
			writel((readl(pgpf3con + DAT) & ~(1 << (ledno + 1))) | (cmd << (ledno + 1)),pgpf3con + DAT);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}

static struct file_operations fs4412_leds_ops ={
	.owner			= THIS_MODULE,
	.open			= fs4412_leds_open,        		//对应open();
	.release		= fs4412_leds_release,    		//对应close();
	.unlocked_ioctl = fs4412_leds_ioctl,		//对应ioctl();
};

static int fs4412_leds_platform_probe(struct platform_device *pdev)
{
    int ret;
	printk("match\n");

    /*1.注册设备号 和 字符设备  */
	ret = register_chrdev(major, "leds", &fs4412_leds_ops);
	if(ret<0)
	{
		printk("fail \n");
		return ret;
	}
    /*2.自动创建设备节点*/
	cls = class_create(THIS_MODULE, "mycls");
	devno = MKDEV(major,minor);
	tst_device = device_create(cls, NULL, devno, NULL, "leds");

    /*3. 硬件初始化*/
    /*3.1 内存映射*/
	pgpx2con = ioremap(pdev->resource[0].start, pdev->resource[0].end - pdev->resource[0].start);
	pgpx1con = ioremap(pdev->resource[1].start, pdev->resource[1].end - pdev->resource[1].start);
	pgpf3con = ioremap(pdev->resource[2].start, pdev->resource[2].end - pdev->resource[2].start);

    /*3.2 初始化led*/
	fs4412_leds_init();
    return 0;
}

static int fs4412_leds_platform_remove(struct platform_device *pdev)
{
	printk("remove\n");

    /*1. 取消内存映射*/
	fs4412_leds_iounmap();
    /*2. 注销设备节点和类*/
	device_destroy(cls, devno);
	class_destroy(cls);

    /*3.注销字符设备*/
	unregister_chrdev(major, "leds");
    return 0;
}
static struct platform_driver pdrv = {

	.probe          = fs4412_leds_platform_probe,   //
	.remove         = fs4412_leds_platform_remove,  //
   // void (*shutdown)(struct platform_device *);
   // int (*suspend)(struct platform_device *, pm_message_t state);
   // int (*resume)(struct platform_device *);
   // struct device_driver driver;
    .driver.name    = "leds_device",    //设备名 驱动和设备通过它识别
   // const struct platform_device_id *id_table;
   // bool prevent_deferred_probe;
};


static int fs4412_leds_platform_driver_init(void)
{

	printk("fs4412_leds_platform_driver_init()\n");
    return platform_driver_register(&pdrv);
}
static void fs4412_leds_platform_driver_exit(void)
{
	printk("fs4412_leds_platform_driver_exit()\n");
    platform_driver_register(&pdrv);
	return;
}
MODULE_LICENSE("GPL");
module_init(fs4412_leds_platform_driver_init);
module_exit(fs4412_leds_platform_driver_exit);




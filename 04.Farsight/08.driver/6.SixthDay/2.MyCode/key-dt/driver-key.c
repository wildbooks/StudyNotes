#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <asm/io.h>
#include <linux/fs.h>

/*              裸机中的一些原理
	1.设置GPIO
		1.设置引脚为中断模式  GPX1CON
		2.禁止内部上下拉      GPX1PUD
		3.设置中断触发方式    EXT_INT41_CON
		4.相应引脚中断使能    EXT_INT41_MASK
		5.中断状态寄存器      EXT_INT41_PEND
			中断完成后需要清除相应位
		6.中断滤波            EXT_INT41_FLTCON0
	2.设置分配器
		1.使能分配器 ICDDCR = 1
		2.使能相应中断到分配器中 ICDISER.ICDISER1
		3.设置SPI25/SPI26由哪个cpu处理,当前设置cpu0
			ICDIPTR.ICDIPTR14
	3.选择CPU接口
		2.全局使能cpu0中断处理 CPU0.ICCICR
		3.优先级屏蔽寄存器，设置CPU0能处理所有的中断
			CPU0.ICCPMR = 0xff
	4.中断处理函数
		获取中断号irq_num = (CPU0.ICCIAR & 0x3FF)
	4.清除中断状态位
		1.外设级：EXT_INT41_PEND
		2.GIC级：ICDICPR.ICDICPR1
		3.CPU级：CPU0。ICCEOIR
*/

/*
	UART_RING -- EINT9 -- GPX1_1 -- K2 -- 57
	SIM_DET -- EINT10 -- GPX1_2 -- K3 -- 58
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


static struct file_operations fs4412_key_ops ={
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
	ret = register_chrdev(major, "key", &fs4412_leds_ops);
	if(ret<0)
	{
		printk("fail \n");
		return ret;
	}
    /*2.自动创建设备节点*/
	cls = class_create(THIS_MODULE, "mycls");
	devno = MKDEV(major,minor);
	tst_device = device_create(cls, NULL, devno, NULL, "key");

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
	unregister_chrdev(major, "key");
    return 0;
}
static struct of_device_id fs4412_key_tbl[] ={
    {.compatible = "fs4412,key"},
};

static struct platform_driver pdrv = {

	.probe          = fs4412_key_platform_probe,   //
	.remove         = fs4412_key_platform_remove,  //
   // void (*shutdown)(struct platform_device *);
   // int (*suspend)(struct platform_device *, pm_message_t state);
   // int (*resume)(struct platform_device *);
   // struct device_driver driver;
    .driver={
        .name    = "key-device",  // 驱动和设备通过它识别,为什么不能省
        .of_match_table = fs4412_key_tbl,   //设备树中，匹配靠的是这个
    }
   // const struct platform_device_id *id_table;
   // bool prevent_deferred_probe;
};


static int fs4412_key_platform_driver_init(void)
{

	printk("fs4412_key_platform_driver_init()\n");
    return platform_driver_register(&pdrv);
}
static void fs4412_key_platform_driver_exit(void)
{
	printk("fs4412_key_platform_driver_exit()\n");
    platform_driver_register(&pdrv);
	return;
}
MODULE_LICENSE("GPL");
module_init(fs4412_key_platform_driver_init);
module_exit(fs4412_key_platform_driver_exit);




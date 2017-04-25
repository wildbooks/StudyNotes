#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>

/*
	1.LED2 -- LED5
	GPX2_7 GPX1_0	GPF3_4	GPF3_5
*/


#define GPX2CON   	0x11000C40
//#define GPX2DAT 	0x11000C44
#define GPX1CON   	0x11000C20
//#define GPX1DAT    	0x11000C24
#define GPF3CON  	0x114001E0
//#define GPF3DAT   	0x114001E4

static void	fs4412_leds_device_release(struct device *dev)
{
    return;
}
static struct resource fs4412_leds_resource[] ={
    [0] ={
	.start      = GPX2CON,
	.end        = GPX2CON + 0x8,
    .flags      = IORESOURCE_MEM,
    },

    [1] ={
	.start      = GPX1CON,
	.end        = GPX1CON + 0x8,
    .flags      = IORESOURCE_MEM,
    },

    [2] ={
	.start      = GPF3CON,
	.end        = GPF3CON + 0x8,
    .flags      = IORESOURCE_MEM,
    },
};
static struct platform_device pdev = {
    .name           = "leds_device",        //设备名   通过设备名识别
	.id             = -1,                   //用于标识设备的ID
	//bool		id_auto;                    //指示在注册设备时是否自动赋予ID值
	.dev.release    = fs4412_leds_device_release,   //真正的设备
	.num_resources  = 3,                    //资源的个数

	//struct resource	*resource;          //资源
    .resource       = fs4412_leds_resource,
	//const struct platform_device_id	*id_entry;//支持的驱动名称

	/* MFD cell pointer */
	//struct mfd_cell *mfd_cell;

	/* arch specific additions */
	//struct pdev_archdata	archdata;
};
static int fs4412_leds_platform_device_init(void)
{
	printk("fs4412_leds_platform_device_init()\n");
    /*platform设备注册*/
    return platform_device_register(&pdev);
}
static void fs4412_leds_platform_device_exit(void)
{
	printk("fs4412_leds_platform_device_exit()\n");
    /*platform设备注销*/
    platform_device_unregister(&pdev);
	return;
}


MODULE_LICENSE("GPL");
module_init(fs4412_leds_platform_device_init);
module_exit(fs4412_leds_platform_device_exit);




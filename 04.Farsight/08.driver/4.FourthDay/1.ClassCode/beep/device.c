#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>

static void	fs4412_dev_release(struct device *dev)
{
	return;
}
/*
#define GPD0CON       0x114000a0
#define FS4412TIMER_BASE    0x139D0000
*/

struct resource beep_resource[]={
	[0]={
		.start = 0x114000a0,
		.end  = 0x114000a0+0x4,
		.flags = IORESOURCE_MEM,
	},
	[1]={
		.start = 0x139D0000,
		.end  = 0x139D0000+0x14,
		.flags = IORESOURCE_MEM,
	},
};

struct platform_device pdev = 
{
	.name = "zhongqiu",
	.id =-1,
	.dev.release = fs4412_dev_release,
	.num_resources = ARRAY_SIZE(beep_resource),
	.resource = beep_resource,
};

int hello_init(void)
{
	printk("hello_init()\n");
	return platform_device_register(&pdev);
}
void hello_exit(void)
{
	printk("hello_exit()\n");
	platform_device_unregister(&pdev);
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

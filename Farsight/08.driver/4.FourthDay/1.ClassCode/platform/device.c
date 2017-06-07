#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>

static void	fs4412_dev_release(struct device *dev)
{
	return;
}

struct platform_device pdev = 
{
	.name = "zhongqiu",
	.id =-1,
	.dev.release = fs4412_dev_release,
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


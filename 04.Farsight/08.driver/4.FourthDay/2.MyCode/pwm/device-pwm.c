#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>

/*
 *  beep  GPD0_0    XpwmTOUT0
 *      GPD0CON[3:0]=0x1
 */


#define GPD0CON     0x114000A0
#define PWM_BASE    0x139D0000

#define TCFG0       0x0000
#define TCFG1       0x0004
#define TCON        0x0008
#define TCNTB0      0x000C
#define TCMPB0      0x0010
#define TCNTO0      0x0014



static void	fs4412_pwm_device_release(struct device *dev)
{
    return;
}
static struct resource fs4412_pwm_resource[] ={
    [0] ={
	.start      = GPD0CON,
	.end        = GPD0CON + 0x4,
    .flags      = IORESOURCE_MEM,
    },

    [1] ={
	.start      = PWM_BASE,
	.end        = PWM_BASE + TCNTO0 + 0x4,
    .flags      = IORESOURCE_MEM,
    }
};
static struct platform_device pdev = {
    .name           = "pwm_device",        //设备名   通过设备名识别
	.id             = -1,                   //用于标识设备的ID
	//bool		id_auto;                    //指示在注册设备时是否自动赋予ID值
	.dev.release    = fs4412_pwm_device_release,   //真正的设备
	.num_resources  = 2,                    //资源的个数

	//struct resource	*resource;          //资源
    .resource       = fs4412_pwm_resource,
	//const struct platform_device_id	*id_entry;//支持的驱动名称

	/* MFD cell pointer */
	//struct mfd_cell *mfd_cell;

	/* arch specific additions */
	//struct pdev_archdata	archdata;
};
static int fs4412_pwm_platform_device_init(void)
{
	printk("fs4412_pwm_platform_device_init()\n");
    /*platform设备注册*/
    return platform_device_register(&pdev);
}
static void fs4412_pwm_platform_device_exit(void)
{
	printk("fs4412_pwm_platform_device_exit()\n");
    /*platform设备注销*/
    platform_device_unregister(&pdev);
	return;
}


MODULE_LICENSE("GPL");
module_init(fs4412_pwm_platform_device_init);
module_exit(fs4412_pwm_platform_device_exit);




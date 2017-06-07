#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <asm/io.h>
#include <linux/fs.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/uaccess.h>

/*
    http://blog.chinaunix.net/uid-25002135-id-3016304.html
 */
/*
   TEMP_OUT  -- GPK1_1
   */

static int major = 250;
static int minor = 0;
static dev_t devno;
static struct class *cls;
static struct device *tst_device;
static spinlock_t lock;

static void * pgpk1con;
#define DAT         0x4     //偏移量
#define PUD         0x8     //偏移量



/*配置为输出*/
static void set_conOUT(void)
{
    writel((readl(pgpk1con) & ~(0xf<<4)) | (0x1 <<4), pgpk1con);
}

/*配置为输入*/
static void set_conIN(void)
{
    writel(readl(pgpk1con) & ~(0xf<<4), pgpk1con);
}

/*置位*/
static void set_data(int i)
{
    writel((readl(pgpk1con + DAT) & ~(0x1<<1)) | (i<<1), pgpk1con+DAT);
}

/*复位ds18b20*/
/*
    Tx:主机拉低电平480~960um,再拉高并设置为输入模式
    Rx:

 */
static  char reset_ds18b20(void)
{
    char ret;
    /*Tx*/
    set_conOUT();
    set_data(0);
    udelay(600);    /*复位脉冲 480~960um*/
    set_data(1);    /*再拉高电压,释放总线*/

    /*Rx*/
    set_conIN();    /*设置为输入模式,外部上拉拉高*/
    udelay(100);     /*等待15~60um +60-240um下降沿*/
    ret = (readl(pgpk1con + DAT)>>1) & 0x1;/*从设备拉低电压,大概60-240um*/
    udelay(200);     /*等待15~60um*/
    /*稍做延时后，如果x=0则初始化成功,x=1,初始化失败*/
    if(ret)
        printk("init is error: %d\n", ret);
    else
        printk("init is success: %d\n", ret);
    return ret;
}

/*读取1位温度*/
static char read_bit(void)
{
    char dat;
    //spin_lock(&lock);
    set_conOUT();
    set_data(0);
    udelay(2);
    set_data(1);    //add
    set_conIN();
    udelay(10);
    //spin_unlock(&lock);
    dat = (readl(pgpk1con + DAT)>>1) & 0x1;
    udelay(2);
    return dat;
}

/*读取值*/
static char read_val(void)
{
    char temp = 0;
    char i;
    for(i=0; i<8; i++){
        if(read_bit())
            temp |= read_bit()<<i;
        udelay(62);
    }
    return temp;
}
/*写1位命令 只能是0 1*/
static void write_bit(char bitvalue)
{
    //spin_lock(&lock);
    set_conOUT();
    set_data(0);
    udelay(15);
    set_data(bitvalue);
    //spin_unlock(&lock);
    udelay(45);
    set_conIN();
    udelay(2);
}
/*写命令*/
static void write_cmd(char cmd)
{
    char temp;
    char i;
    for(i=0; i<8; i++){
        temp = cmd & 0x1;
        cmd >>= 1;
        write_bit(temp);
    }

}
/*读操作*/


static void fs4412_ds18b20_iounmap(void)
{
    iounmap(pgpk1con);
}

static void fs4412_ds18b20_init(void)
{
    /*禁止上下拉*/
    writel(readl(pgpk1con + PUD) & ~(0x3<<2), pgpk1con + PUD);
}


static int fs4412_ds18b20_open(struct inode *inode, struct file *file)
{
    printk("fs4412_ds18b20_open\n");
    fs4412_ds18b20_init();
    spin_lock_init(&lock);
    return 0;
}
static int fs4412_ds18b20_release(struct inode *inode, struct file *file)
{
    printk("fs4412_ds18b20_release\n");
    return 0;
}

static ssize_t fs4412_ds18b20_read(struct file *filp, char __user *buffer, size_t size, loff_t *ppos)
{
    char val[2];
    if(reset_ds18b20())
        printk("init error\n");
    udelay(400);
    set_conOUT();
    set_data(1);
    write_cmd(0xCC);    //跳过rom命令
    write_cmd(0x44);    //转换温度
    udelay(1000);

    if(reset_ds18b20())
        printk("init error\n");
    udelay(400);
    set_conOUT();
    set_data(1);
    write_cmd(0xCC);    //跳过rom命令
    write_cmd(0xBE);    //读命令
    udelay(1000);

    /*读取转换温度*/
    val[0] = read_val();
    val[1] = read_val();
    copy_to_user(buffer, val, sizeof(val));
    return 0;
}

static struct file_operations fs4412_ds18b20_ops ={
    .owner			= THIS_MODULE,
    .open			= fs4412_ds18b20_open,        		//对应open();
    .read           = fs4412_ds18b20_read,
    .release		= fs4412_ds18b20_release,    		//对应close();
};

static int fs4412_ds18b20_platform_probe(struct platform_device *pdev)
{
    int ret;
    printk("match\n");

    /*1.注册设备号 和 字符设备  */
    ret = register_chrdev(major, "ds18b20", &fs4412_ds18b20_ops);
    if(ret<0)
    {
        printk("fail \n");
        return ret;
    }
    /*2.自动创建设备节点*/
    cls = class_create(THIS_MODULE, "ds18b20cls");
    devno = MKDEV(major,minor);
    tst_device = device_create(cls, NULL, devno, NULL, "ds18b20");

    /*3. 硬件初始化*/
    /*3.1 内存映射*/
    pgpk1con = ioremap(pdev->resource[0].start, pdev->resource[0].end - pdev->resource[0].start);

    /*3.2 初始化led*/
    fs4412_ds18b20_init();
    return 0;
}

static int fs4412_ds18b20_platform_remove(struct platform_device *pdev)
{
    printk("remove\n");

    /*1. 取消内存映射*/
    fs4412_ds18b20_iounmap();
    /*2. 注销设备节点和类*/
    device_destroy(cls, devno);
    class_destroy(cls);

    /*3.注销字符设备*/
    unregister_chrdev(major, "leds");
    return 0;
}
static struct of_device_id fs4412_leds_tbl[] ={
    {.compatible = "fs4412,ds18b20"},
};

static struct platform_driver pdrv = {

    .probe          = fs4412_ds18b20_platform_probe,   //
    .remove         = fs4412_ds18b20_platform_remove,  //
    // void (*shutdown)(struct platform_device *);
    // int (*suspend)(struct platform_device *, pm_message_t state);
    // int (*resume)(struct platform_device *);
    // struct device_driver driver;
    .driver={
        .name    = "ds18b20",  // 驱动和设备通过它识别,为什么不能省
        .of_match_table = fs4412_leds_tbl,
    }
    // const struct platform_device_id *id_table;
    // bool prevent_deferred_probe;
};


static int fs4412_ds18b20_platform_driver_init(void)
{

    printk("fs4412_ds18b20_platform_driver_init()\n");
    return platform_driver_register(&pdrv);
}
static void fs4412_ds18b20_platform_driver_exit(void)
{
    printk("fs4412_ds18b20_platform_driver_exit()\n");
    platform_driver_register(&pdrv);
    return;
}
MODULE_LICENSE("GPL");
module_init(fs4412_ds18b20_platform_driver_init);
module_exit(fs4412_ds18b20_platform_driver_exit);




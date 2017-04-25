#include<linux/fs.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include <linux/cdev.h>
#include <linux/i2c.h>
#include<linux/uaccess.h>
#include<linux/device.h>
#include<asm/io.h>
#include<asm/ioctl.h>
#include<linux/string.h>
#include "head.h"

#define SELF_TEST_X 0x0D
#define SELF_TEST_Y 0x0E
#define SELF_TEST_Z 0x0F
#define SELF_TEST_A 0x10

#define SMPRT_DIV 0x19  //采样率 0x07
#define GYRO_CONFIG 0x1B  //陀螺仪配置寄存器  0x18
#define ACCEL_CONFIG 0x1C //加速检测仪
/*加速度寄存器*/
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C

#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E

#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

/*温度寄存器*/
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
/*陀螺仪角速度*/
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44

#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46

#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
/*电源管理 以及I2C地址寄存器*/
#define PWR_MGMT_1 0x6B       // 0
#define WHO_AM_I   0x75       //0x68


#define MMARJOR 250   //主设备号
#define MMINOR  0     //次设备号
static dev_t devnm;
static int ret;

static struct i2c_client *mpu6050_client; //描述一个从设备
static void mpu6050_write(unsigned char reg , unsigned char var)  //第一个参数是地址，第二个参数是要写的参数
{
    unsigned char txbuf[2]={reg,var};
    struct i2c_msg msgs[]={             //消息
        {mpu6050_client->addr,0,2,txbuf},
    };
                //适配器
    i2c_transfer(mpu6050_client->adapter,msgs,ARRAY_SIZE(msgs));
}
static unsigned char mpu6050_read(unsigned char reg)  //第一个参数是地址，第二个参数是要写的参数
{
    unsigned char txbuf[1]={reg};
    unsigned char rxbuf[1]={0};
    struct i2c_msg msgs[]={
        {mpu6050_client->addr,0,1,txbuf},
        {mpu6050_client->addr,1,1,rxbuf},
    };
    i2c_transfer(mpu6050_client->adapter,msgs,ARRAY_SIZE(msgs));
    return rxbuf[0];
}
static int mpu6050_open(struct inode *inode,struct file *file)
{
    printk("open success\n");
    return 0;
}
//ssize_t mpu6050_read(struct file *file, char __user *user, size_t size, loff_t *lf)
//{
//	printk("read success\n");
//	return 0;
//}
static long mpu6050_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{

    struct mpu6050_data data;
    memset(&data,0,sizeof(data));

    /*获取温度*/
    if(cmd == MPU6050_GET_TEMP)
    {
        data.temp= mpu6050_read(TEMP_OUT_L);
        data.temp |= mpu6050_read(TEMP_OUT_H) << 8;
    }
    /*获取角速度*/
    if(MPU6050_GET_GYRO==cmd)
    {
        data.x = mpu6050_read(GYRO_XOUT_L);
        data.x |= mpu6050_read(GYRO_XOUT_H) << 8;
        data.y = mpu6050_read(GYRO_YOUT_L);
        data.y |= mpu6050_read(GYRO_YOUT_H) << 8;
        data.z = mpu6050_read(GYRO_ZOUT_L);
        data.z |= mpu6050_read(GYRO_ZOUT_H) << 8;

    }

    /*获取加数度*/
    if(MPU6050_GET_ACCEL ==cmd)
    {

        data.x = mpu6050_read(ACCEL_XOUT_L);
        data.x |= mpu6050_read(ACCEL_XOUT_H) << 8;
        data.y = mpu6050_read(ACCEL_YOUT_L);
        data.y |= mpu6050_read(ACCEL_YOUT_H) << 8;
        data.z = mpu6050_read(GYRO_ZOUT_L);
        data.z |= mpu6050_read(ACCEL_ZOUT_H) << 8;

    }
    if(copy_to_user((void *)arg,&data,sizeof(data)))
    {
        ;
    }
    return 0;
}

static struct file_operations mpu6050_ops={
    .open=mpu6050_open,
    //	.read=mpu6050_read,
    .unlocked_ioctl = mpu6050_ioctl,
};
static struct cdev rdev;

static int mpu6050_remove(struct i2c_client *client)
{
    cdev_del(&rdev);
    unregister_chrdev_region(devnm,1);//释放设备号；
    printk("remove OK\n");
    return 0 ;
}
static int mpu6050_probe(struct i2c_client *client, const struct i2c_device_id *i2c_id)
{
    mpu6050_client = client;
    devnm=MKDEV(MMARJOR,MMINOR);
    /*申请设备号*/
    if((ret=register_chrdev_region(devnm,1,"mpu6050_jiao"))!=0)
    {
        printk("register_chrdev_region fail\n");

        return ret;
    }

    /*初始化设备*/
    cdev_init(&rdev,&mpu6050_ops);
    /*注册设备*/
    ret=cdev_add(&rdev,devnm,1);
    if(ret<0)
    {
        printk("fail to cdev\n");
        /*注销设备号*/
        unregister_chrdev_region(devnm,1);

    }
    mpu6050_write(PWR_MGMT_1,0x00);
    mpu6050_write(SMPRT_DIV, 0x07);
    mpu6050_write(GYRO_CONFIG,0x18);
    mpu6050_write(ACCEL_CONFIG,0x01);

    printk("match ok\n");
    return 0;
}

static struct of_device_id mpu6050_table[]={
    {
        .compatible="invensense,mpu6050",

    },

};
static struct i2c_device_id mpu6050_id_table[]={

    {
        "mpu6050",0,   //匹配属性后面的设备

    },
};
static struct i2c_driver mpu6050_driver = {
    .driver ={
        .name = "mpu6050",
        .of_match_table = mpu6050_table,//通过它匹配
    },
    .probe = mpu6050_probe,
    .remove = mpu6050_remove,
    .id_table = mpu6050_id_table, //资源


};
static int mpu6050_init(void)
{

    i2c_add_driver(&mpu6050_driver);
    printk("mpu6050_init  \n");
    return 0;
}
void mpu6050_exit(void)
{

    i2c_del_driver(&mpu6050_driver);
    printk("mpu6050_exit  \n");
    return ;
}


MODULE_LICENSE("GPL");
module_init(mpu6050_init);
module_exit(mpu6050_exit);

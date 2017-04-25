/*
 *@brief	This example describes how to use I2C
 *@date:	12. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"
#include "uart.h"


//****************************************
//	MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取


/*
 * Irq_rutine
 * */
void do_irq() {

}


/**********************************************************************
 * @brief		mydelay_ms_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void mydelay_ms(int time)
{
	int i, j;
	while(time--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}

/**********************************************************************
 * @brief		iic write a byte program body
 * @param[in]	slave_addr, addr, data
 * @return 		None
 **********************************************************************/
void iic_write (unsigned char slave_addr, unsigned char addr, unsigned char data)
{
	I2C5.I2CDS = slave_addr;
	I2C5.I2CCON = 1<<7 | 1<<6 | 1<<5;/*ENABLE ACK BIT, PRESCALER:512, ,ENABLE RX/TX */
	I2C5.I2CSTAT = 0x3 << 6 | 1<<5 | 1<<4;/*Master Trans mode ,START ,ENABLE RX/TX ,*/
	while(!(I2C5.I2CCON & (1<<4)));

	I2C5.I2CDS = addr;
	I2C5.I2CCON &= ~(1<<4);	//Clear pending bit to resume.
	while(!(I2C5.I2CCON & (1<<4)));

	I2C5.I2CDS = data;	// Data
	I2C5.I2CCON &= ~(1<<4);	//Clear pending bit to resume.
	while(!(I2C5.I2CCON & (1<<4)));

	I2C5.I2CSTAT = 0xD0; //stop

	I2C5.I2CCON &= ~(1<<4);

	mydelay_ms(10);
}


/**********************************************************************
 * @brief		iic read a byte program body
 * @param[in]	slave_addr, addr, &data
 * @return 		None
 **********************************************************************/
void iic_read(unsigned char slave_addr, unsigned char addr, unsigned char *data)
{
	I2C5.I2CDS = slave_addr;

	I2C5.I2CCON = 1<<7 | 1<<6 | 1<<5;/*ENABLE ACK BIT, PRESCALER:512, ,ENABLE RX/TX */
	I2C5.I2CSTAT = 0x3 << 6 | 1<<5 | 1<<4;/*Master Trans mode ,START ,ENABLE RX/TX ,*/
	while(!(I2C5.I2CCON & (1<<4)));

	I2C5.I2CDS = addr;
	I2C5.I2CCON &= ~(1<<4);	//Clear pending bit to resume.
	while(!(I2C5.I2CCON & (1<<4)));
	I2C5.I2CSTAT = 0xD0; //stop


	I2C5.I2CDS = slave_addr | 0x01;	// Read
	I2C5.I2CCON = 1<<7 | 1<<6 | 1<<5;/*ENABLE ACK BIT, PRESCALER:512, ,ENABLE RX/TX */

	I2C5.I2CSTAT = 2<<6 | 1<<5 | 1<<4;/*Master receive mode ,START ,ENABLE RX/TX ,*/
	while(!(I2C5.I2CCON & (1<<4)));

	I2C5.I2CCON &= ~((1<<7) | (1<<4));/* Resume the operation  & no ack*/
	while(!(I2C5.I2CCON & (1<<4)));

	I2C5.I2CSTAT = 0x90;
	I2C5.I2CCON &= ~(1<<4);		/*clean interrupt pending bit  */

	*data = I2C5.I2CDS;
	mydelay_ms(10);
}


/**********************************************************************
 * @brief		MPU6050_Init program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void MPU6050_Init ()
{
	iic_write(SlaveAddress, PWR_MGMT_1, 0x00);
	iic_write(SlaveAddress, SMPLRT_DIV, 0x07);
	iic_write(SlaveAddress, CONFIG, 0x06);
	iic_write(SlaveAddress, GYRO_CONFIG, 0x18);
	iic_write(SlaveAddress, ACCEL_CONFIG, 0x01);
}

/**********************************************************************
 * @brief		get MPU6050 data program body
 * @param[in]	addr
 * @return 		int
 **********************************************************************/
int get_data(unsigned char addr)
{
	char data_h, data_l;
	iic_read(SlaveAddress, addr, &data_h);
	iic_read(SlaveAddress, addr+1, &data_l);
	return (data_h<<8)|data_l;
}

/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void)
{
	int data;

	unsigned char zvalue;

	GPX2.CON = 0x1 << 28;

	GPB.CON = (GPB.CON & ~(0xF<<12)) | 0x3<<12; // GPBCON[3], I2C_5_SCL
	GPB.CON = (GPB.CON & ~(0xF<<8)) | 0x3<<8;	// GPBCON[2], I2C_5_SDA

	mydelay_ms(100);
	uart_init();

/*---------------------------------------------------------------------*/
	I2C5.I2CSTAT = 0xD0;
	I2C5.I2CCON &= ~(1<<4);		/*clean interrupt pending bit  */
/*---------------------------------------------------------------------*/

	mydelay_ms(100);
	MPU6050_Init();
	mydelay_ms(100);

	printf("\n********** I2C test!! ***********\n");

	while(1)
	{
		//Turn on
		GPX2.DAT |= 0x1 << 7;

		data = get_data(GYRO_ZOUT_H);
		printf(" GYRO --> Z <---:Hex: %0x", data);
		printf("\n");

		mydelay_ms(20);
		//Turn off
		GPX2.DAT &= ~(0x1 << 7);
		mydelay_ms(500);
	}
	return 0;
}

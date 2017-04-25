/*
 *@brief	This example describes how to use 1-Wire interface to drive
 *			DS18B20 Digital Thermometer
 *@date:	12. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"
#include "uart.h"

/*
 * Irq_rutine
 * */
void do_irq() {

}


/**********************************************************************
 * @brief		mydelay_us program body,
 * 				approximate 0.9us
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void delay_us(int time) {
	time <<= 2;
	while(time--);
}


/**********************************************************************
 * @brief		mydelay_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void delay_ms(int time)
{
	int i, j;
	while(time--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}



void print_temp(unsigned char Temp1, unsigned char Temp2)
{
	char sign = '+';
	unsigned int Temperature;

	printf("\n");

	if(Temp2 & 0xFC)
	{
		sign = '-';
		Temperature = ((Temp2 << 8) | Temp1);

		Temperature = ((~Temperature) + 1) & 0xFFFF;
		Temperature *= 0.0625 * 10 * 10;
	}
	else
	{
		sign = '+';
		Temperature = ((Temp2 << 8) | Temp1);
		Temperature *= 0.0625 * 10 * 10;
	}
	printf("Temperature: %c%d.%d%d\n", sign, \
									   Temperature/100, \
									   Temperature%100/10, \
									   Temperature%100%10);

}

/**********************************************************************
 * @brief		DS18_Reset program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void DS18_Reset()
{
	GPK1.PUD = 0; 	//disable Pull-up/Pull-down
	GPK1.CON = (GPK1.CON & ~(0xF << 4)) | 0x1 << 4; //Output
	GPK1.DAT &= ~(0x1 << 1);	//Output '0'


	delay_us(700); //delay 600us


	GPK1.DAT |= 0x1 << 1;		//Output '1'

	GPK1.CON &= ~(0xF << 4);	//Input

	while(GPK1.DAT & (0x1 << 1));
	while(!(GPK1.DAT & (0x1 << 1)));
}


/**********************************************************************
 * @brief		DS18_Write program body, 1-Wire interface write
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void DS18_Write(unsigned char data)
{
	unsigned char i;
	GPK1.CON = (GPK1.CON & ~(0xF << 4)) | 0x1 << 4;  //Output
	GPK1.DAT |= 0x1 << 1;		//Output '1'

	for(i = 0; i < 8; i++)
	{
		GPK1.DAT &= ~(0x1 << 1);	//Output '0'

		delay_us(13);

		if(data & 0x1)
			GPK1.DAT |= 0x1 << 1;		//Output '1'

		delay_us(40);

		data = data / 2;
		GPK1.DAT |= 0x1 << 1;		//Output '1'

	}
}

/**********************************************************************
 * @brief		DS18_Write program body, 1-Wire interface read
 * @param[in]	None
 * @return 		unsigned char
 **********************************************************************/
unsigned char DS18_Read()
{
	unsigned char i, Temp = 0;
	for(i = 0; i < 8; i++)
	{
		GPK1.CON = (GPK1.CON & ~(0xF << 4)) | 0x1 << 4;
		GPK1.DAT |= 0x1 << 1;		//Output '1'
		Temp >>= 1;
		GPK1.DAT &= ~(0x1 << 1);	//Output '0'

		GPK1.DAT |= 0x1 << 1;		//Output '1'

		GPK1.CON &= ~(0xF << 4);	//Input

		if(GPK1.DAT & (0x1 << 1))
			Temp |= 0x80;

		delay_us(30);
	}
	return Temp;
}

/**********************************************************************
 * @brief		Read_Temperature program body
 * @param[in]	None
 * @return 		unsigned char
 **********************************************************************/
void Read_Temperature (unsigned char *Temp1, unsigned char *Temp2)
{
	DS18_Reset();		//Reset

	delay_us(7);

	DS18_Write(0xCC);  // 0xCC: skip rom command
	DS18_Write(0x44);	//Covert T

	DS18_Reset();		//Reset
	DS18_Write(0xCC);  // 0xCC: skip rom command
	DS18_Write(0xBE);	//Read ram

	*Temp1 = DS18_Read();	// Read the LS Byte
	*Temp2 = DS18_Read();	// Read the MS Byte

	DS18_Reset(); //The end of read
}

/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void)
{
	unsigned char Temp1, Temp2;

	GPX2.CON = 0x1 << 28;  //Led

	uart_init();

	printf("\n****************DS18 Temperature test*****************\n");

	while(1)
		{
			GPX2.DAT = GPX2.DAT | 0x1 << 7;		//Turn on	Led

			Read_Temperature(&Temp1, &Temp2);
			delay_ms(500);

			GPX2.DAT = GPX2.DAT & ~(0x1 << 7);	//Turn off	Led
			delay_ms(500);

			print_temp(Temp1, Temp2);
		}
	return 0;
}

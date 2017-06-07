/*
 *@brief	This example describes how to use UART
 *@date:	12. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"

void mydelay(int time);


/**********************************************************************
 * @brief		mydelay_ms program body
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
 * @brief		uart_init, Normal mode, No parity,One stop bit,8 data bits
 * 				Buad-reate : 115200, clock srouce 100Mhz
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void uart_init(void)
{

	/*UART2 initialize*/
	GPA1.GPA1CON = (GPA1.GPA1CON & ~0xFF ) | (0x22); //GPA1_0:RX;GPA1_1:TX

	UART2.ULCON2 = 0x3; //Normal mode, No parity,One stop bit,8 data bits
	UART2.UCON2 = 0x5;  //Interrupt request or polling mode


	/*
	 * Baud-rate 115200: src_clock:100Mhz
	 * DIV_VAL = (100*10^6 / (115200*16) -1) = (54.3 - 1) = 53.3
	 * UBRDIV2 = (Integer part of 53.3) = 53 = 0x35
	 * UFRACVAL2 = 0.3*16 = 0x5
	 * */
	UART2.UBRDIV2 = 0x35;
	UART2.UFRACVAL2 = 0x5;
}

void putc(const char data)
{
	while(!(UART2.UTRSTAT2 & 0X2));
	UART2.UTXH2 = data;
	if (data == '\n')
			putc('\r');
}
void puts(const  char  *pstr)
{
	while(*pstr != '\0')
		putc(*pstr++);
}

unsigned char getchar()
{
	unsigned char c;
	while(!(UART2.UTRSTAT2 & 0X1));
	c = UART2.URXH2;
	return c;
}

/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void) {

	char c, str[] = "uart test!! \n";

	//LED
	GPX2.GPX2CON = 0x1 << 28;
	uart_init();

	while(1)
		{
			//Turn on LED
			GPX2.GPX2DAT = GPX2.GPX2DAT | 0x1 << 7;
			puts(str);
			mydelay_ms(500);
			//Turn off LED
			GPX2.GPX2DAT = GPX2.GPX2DAT & ~(0x1 << 7);
			mydelay_ms(500);
		}
	return 0;
}

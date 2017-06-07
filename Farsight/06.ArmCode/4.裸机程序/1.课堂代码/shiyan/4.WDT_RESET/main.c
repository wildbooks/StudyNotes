/*
 *@brief	This example describes how to use WDT generate reset signal
 *@date:	12. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"
#include "uart.h"

/**********************************************************************
 * @brief		IRQ Interrupt Service Routine program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void do_irq(void)
{
}

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

void wdt_init()
{
	WDT.WTCNT = 0x2014;	//initial value

	/*
	*Prescaler value:255,  Enables WDT
	*Prescaler clock division factor 128
	*Enables WDT reset signal
	*/
	WDT.WTCON = 0xff<<8 | 1<<5 | 3<<3 | 1;
}


/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void)
{
	GPX2.CON = 0x1 << 28;
	uart_init();

	wdt_init();

	printf("\n ************* WDT RESET test!! ***************\n");

	while(1)
		{
			//Turn on	LED2
			GPX2.DAT = GPX2.DAT | 0x1 << 7;
			mydelay_ms(200);
#if 0
			// Feed Dog
			WDT.WTCNT = 0x2014;
#endif
			printf("working...\n");
			//Turn off	LED2
			GPX2.DAT = GPX2.DAT & ~(0x1 << 7);
			mydelay_ms(200);
		}
	return 0;
}

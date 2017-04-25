/*
 *@brief	This example describes how to use WDT generate interrupt
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

	int irq_num;
	irq_num = (CPU0.ICCIAR & 0x1FF);

	printf("\n ******* RTC_ALARM  interrupt !!********\n");
	WDT.WTCLRINT = 1;
	// End of interrupt
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~(0x1FF)) | irq_num;

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
	*Enables WDT interrupt
	*/
	WDT.WTCON = 0xff<<8 | 1<<5 | 3<<3 | 1<<2 ;
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

	/*
	 * GIC interrupt controller:
	* */
		// Enables the corresponding interrupt SPI43, WDT
		ICDISER.ICDISER2 |= 1<<11;  //ICDISER2:spi 32[bit0] ~ 63[bit31], 43 - 32 = [bit11]

		CPU0.ICCICR |= 0x1; //Global enable for signaling of interrupts
		CPU0.ICCPMR = 0xFF; //The priority mask level.Priority filter. threshold

		ICDDCR = 1; 	//Bit1:  GIC monitors the peripheral interrupt signals and
						//		forwards pending interrupts to the CPU interfaces2

		//ICDIPTR18:SPI40~SPI43; SPI43  interrupts are sent to processor 0
		ICDIPTR.ICDIPTR18 = (ICDIPTR.ICDIPTR18 & ~(0xFF<<24)) | 1<<24;
	wdt_init();

	printf("\n****************WDT Interrupt test!!***************\n");

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

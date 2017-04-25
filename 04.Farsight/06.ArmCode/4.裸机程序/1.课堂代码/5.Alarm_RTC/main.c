/*
 *@brief	This example describes how to use RTC's alarm function
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

	RTCINTP |= 0x2;
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


/**********************************************************************
 * @brief		RTC_init, second, minute, hour, day, week, month, year
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void RTC_init()
{
	RTCCON = 0x1;	// Enables RTC control

	RTC.BCDSEC = 0x11;
	RTC.BCDMIN = 0x11;
	RTC.BCDHOUR = 0x11;
	RTC.BCDDAY = 0x11;
	RTC.BCDWEEK = 0x11;
	RTC.BCDMON = 0x11;
	RTC.BCDYEAR = 0x11;

	RTCCON = 0x0;	// Disables RTC control
}

/**********************************************************************
 * @brief		alarm_init
 * 				Disables year, month, day, hour, minute alarm
 * 				Enable second alarm
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void rtc_alarm_init()
{
	RTCALM.ALM = 1;// Disables alarm global, Enables second alarm
	RTCALM.SEC = 0x20; //BCD value for alarm second, 20''
	RTCALM.ALM |= 1<<6;// Enables alarm global

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

	RTC_init();

/*
 * GIC interrupt controller:
* */
	// Enables the corresponding interrupt SPI44, RTC_ALARM
	ICDISER.ICDISER2 |= 1<<12;  //ICDISER2:spi 32[bit0] ~ 63[bit31], 44 - 32 = [bit12]

	CPU0.ICCICR |= 0x1; //Global enable for signaling of interrupts
	CPU0.ICCPMR = 0xFF; //The priority mask level.Priority filter. threshold

	ICDDCR = 1; 	//Bit1:  GIC monitors the peripheral interrupt signals and
					//		forwards pending interrupts to the CPU interfaces2

	ICDIPTR.ICDIPTR19 = (ICDIPTR.ICDIPTR19 & ~(0xFF)) | 0x1;	//SPI44  interrupts are sent to processor 0

	rtc_alarm_init();

	printf("\n****** RTC_ALARM ******* \n");

	while(1)
		{
			//Turn on
			GPX2.DAT = GPX2.DAT | 0x1 << 7;
			mydelay_ms(500);

			printf("year 20%x : month %x : date %x :day %x ", RTC.BCDYEAR,\
														    RTC.BCDMON,\
														    RTC.BCDDAY,\
														    RTC.BCDWEEK );

			printf("hour %x : min %x : sec %x\n",RTC.BCDHOUR, RTC.BCDMIN, RTC.BCDSEC);
			//Turn off
			GPX2.DAT = GPX2.DAT & ~(0x1 << 7);
			mydelay_ms(500);
		}
	return 0;
}

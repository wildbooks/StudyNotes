/*
 *@brief	This example describes how to use ADC conversion by interrupt
 *@date:	12. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"
#include "uart.h"

/*
 *If A/D conversion start by read
 * */
//#define __READ_START_

/**********************************************************************
 * @brief		IRQ Interrupt Service Routine program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void do_irq(void )
{
	unsigned int  temp_adc = 0, temp_mv;

	int irq_num;
	irq_num = (CPU0.ICCIAR & 0x1FF);

	printf("IRQ interrupt !!\n");

	temp_adc = ADCDAT & 0xfff;

	printf("adcdat:  %0x\n", temp_adc);
	//temp_mv = 1800 * temp_adc / 4095;
	temp_mv = 1.8 * 1000 * temp_adc / 0xfff;

	printf("adc value: %d mv\n", temp_mv);

	//Clear SPI Pending
	ICDICPR.ICDICPR1 |= 0x1 << 10;
	//clear ADC pending
	INTADCCLR = 1;
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

/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void)
{
	GPX2.CON = 0x1 << 28;//GPX2CON[7]: Output drive LED

	uart_init();

	ADC_CFG &= ~(0x1 << 16); //Bit_16:Select ADC Mux 0:General 1:MTCADC

	ADCMUX = 0x3;	//0x3: 0011 = AIN3


	/*
	 * GIC interrupt controller:
	 **/
	// Enables the corresponding interrupt SPI10

	ICDISER.ICDISER1 |= 0x1 <<10;
	CPU0.ICCICR |= 0x1; //Global enable for signaling of interrupts

	CPU0.ICCPMR = 0xFF; //The priority mask level.Priority filter. threshold

	ICDDCR = 1; 	//Bit1:  GIC monitors the peripheral interrupt signals and
					//		forwards pending interrupts to the CPU interfaces2

	/***** Interrupt combiner*****/
	INTCOMBINER.IESR2 |= 0x1 << 19;

	ICDIPTR.ICDIPTR10 = 0x01010101;	//SPI8~11  interrupts are sent to processor 0

#ifdef	__READ_START_
	//12bit A/D conversion; enable A/D converter prescaler; prescaler value:255; A/D conversion start by read
	ADCCON = (0x1<<16) | (0x1<<14) | (0xff<<6) | 0x1<<1;
#else
	//12bit A/D conversion; enable A/D converter prescaler; prescaler value:255
	ADCCON = (0x1<<16) | (0x1<<14) | (0x01<<6);
#endif

#ifdef	 __READ_START_
	temp_adc = ADCDAT & 0xfff;
#endif

	printf("\n************ ADC test ************\n");

	while(1)
	{
#ifndef	__READ_START_
		ADCCON |= 0x1;//start ADC conversion
#endif
		//Turn on LED
		GPX2.DAT |= 0x1 << 7;

		mydelay_ms(1000);

		//Turn off LED
		GPX2.DAT &= ~(0x1 << 7);
		mydelay_ms(1000);
	}

	return 0;
}

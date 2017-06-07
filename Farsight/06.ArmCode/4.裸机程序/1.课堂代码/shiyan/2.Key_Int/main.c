/*
 *@brief	This example describes how to use General Interrupt Controller
 *@date:	02. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"

static int num = 0;

/**********************************************************************
 * @brief		IRQ Interrupt Service Routine program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void do_irq(void )
{
	int irq_num;
	irq_num = (CPU0.ICCIAR & 0x1FF);
	switch (irq_num) {

	case 58: //turn on LED2; turn off LED3
		GPX2.GPX2DAT = 0x1 << 7;
		GPX1.GPX1DAT &= ~0x1;
		printf("IRQ interrupt !! turn on LED2; turn off LED3\n");

		//Clear Pend
		EXT_INT41_PEND |= 0x1 << 2;
		ICDICPR.ICDICPR1 |= 0x1 << 26;
		break;
	case 57: //Turn on Led3; Turn off Led2

		GPX2.GPX2DAT &= ~(0x1 << 7);
		GPX1.GPX1DAT |= 0x1;
		printf("IRQ interrupt !! Turn on LED3; Turn off LED2\n");

		//Clear Pend
  		EXT_INT41_PEND |= 0x1 << 1;
		ICDICPR.ICDICPR1 |= 0x1 << 26;
		break;
	}

	// End of interrupt
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~(0x1FF)) | irq_num;

}

/**********************************************************************
 * @brief		mydelay_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void mydelay_ms(int ms)
{
	int i, j;
	while(ms--)
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
	//LED2 GPX2_7
 	GPX2.GPX2CON |= 0x1 << 28;
	//LED3 GPX1_0
	GPX1.GPX1CON |= 0x1;
	//Led4 GPF3_4
	GPF3.GPF3CON |= 0x1 << 16;

	//Key_2  Interrupt  GPX1_1
	GPX1.GPX1PUD = GPX1.GPX1PUD & ~(0x3 << 2); // Disables Pull-up/Pull-down
	GPX1.GPX1CON = (GPX1.GPX1CON & ~(0xF << 4)) | (0xF << 4); //GPX1_1: WAKEUP_INT1[1](EXT_INT41[1])
	EXT_INT41_CON = (EXT_INT41_CON & ~(0x7 << 4)) | 0x2 << 4;
	EXT_INT41_MASK = (EXT_INT41_MASK & ~(0x1 << 1)); //  Bit: 1 = Enables interrupt

	//Key_3  Interrupt  GPX1_2
	GPX1.GPX1PUD = GPX1.GPX1PUD & ~(0x3 << 4); // Disables Pull-up/Pull-down
	GPX1.GPX1CON = (GPX1.GPX1CON & ~(0xF << 8)) | (0xF << 8); //GPX1_2:WAKEUP_INT1[2] (EXT_INT41[2])
	EXT_INT41_CON = (EXT_INT41_CON & ~(0x7 << 8)) | 0x2 << 8;
	EXT_INT41_MASK = (EXT_INT41_MASK & ~(0x1 << 2)); //  Bit: 1 = Enables interrupt


	/*
	 * GIC interrupt controller:
	 * */

	// Enables the corresponding interrupt SPI25, SPI26 -- Key_2, Key_3
	ICDISER.ICDISER1 |= (0x1 << 25) | (0x1 << 26);

	CPU0.ICCICR |= 0x1; //Global enable for signaling of interrupts

	CPU0.ICCPMR = 0xFF; //The priority mask level.Priority filter. threshold

	ICDDCR = 1; 	//Bit1:  GIC monitors the peripheral interrupt signals and
					//		forwards pending interrupts to the CPU interfaces2

	ICDIPTR.ICDIPTR14 = 0x01010101;	//SPI25  SPI26  interrupts are sent to processor 0

	printf("\n ********* GIC test ********\n");

	while (1){
		GPF3.GPF3DAT |= 0x1 << 4;
		mydelay_ms(500);
		GPF3.GPF3DAT &= ~(0x1 << 4);
		mydelay_ms(500);
	}

	return 0;
}

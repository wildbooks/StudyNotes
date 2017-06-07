/*
 *@brief	This example describes how to use PWM to drive BUZZER
 *@date:	02. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"


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


void PWM_init(void)
{
	GPD0.CON = (GPD0.CON & ~(0xf)) | 0x2;// GPD0_0 : TOUT_0

	PWM.TCFG0 = (PWM.TCFG0 & ~(0xFF)) |0x63; //Prescaler 0 value for timer 0; 99 + 1 = 100
	PWM.TCFG1 = (PWM.TCFG1 & ~(0xF)) | 0x3; // 1/8 input for PWM timer 0

	PWM.TCNTB0 = 200;
	PWM.TCMPB0 = 100;

	/* auto-reload, Inverter Off, manual update */
	PWM.TCON = (PWM.TCON & ~(0XF)) | 0XA;
	/* auto-reload, Inverter Off, manual update off, start Timer0*/
	PWM.TCON = (PWM.TCON & ~(0xF)) | 0X9;

}


/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void) {

	GPX2.CON = 0x1 << 28;
	PWM_init();

	while(1)
		{
			//Turn on
			GPX2.DAT = GPX2.DAT | 0x1 << 7;
			//GPD0.DAT |= 0x1;
			mydelay_ms(500);

			//Turn off
			GPX2.DAT = GPX2.DAT & ~(0x1 << 7);
		//	GPD0.DAT &= ~0x1;
			mydelay_ms(500);
		}
	return 0;
}

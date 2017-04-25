/*
 *@brief	This example describes how to use GPIO to drive LEDs
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

/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void)
{
	/*
	 *Config
	 */

	GPX2.CON = (GPX2.CON & ~(0xf<<28))| 1<<28;//GPX2_7:output, LED2
	GPX1.CON = (GPX1.CON & ~(0xf)) | 1; //GPX1_0:output, LED3
	GPF3.CON = (GPX3.CON & ~(0xf<<16 | 0xf<<20)) | (1<<16 | 1<<20);//GPF3_4:output, LED4
																   //GPF3_5:output, LED5

	while(1)
	{
		//Turn on LED2
		GPX2.DAT |= 0x1 << 7;
		mydelay_ms(500);

		//Turn on LED3
		GPX1.DAT |= 0x1;
		//Turn off LED2
		GPX2.DAT &= ~(0x1<<7);
		mydelay_ms(500);

		//Turn on LED5
		GPF3.DAT |= (0x1 << 5);
		//Turn off LED3
		GPX1.DAT &= ~0x1;
		mydelay_ms(500);

		//Turn on LED4
		GPF3.DAT |= (0x1 << 4);
		//Turn off LED5
		GPF3.DAT &= ~(0x1 << 5);
		mydelay_ms(500);

		//Turn off LED4
		GPF3.DAT &= ~(0x1 << 4);


	}
	return 0;
}

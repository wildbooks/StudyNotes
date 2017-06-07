/*************************************************************************
	> File Name: irq.c
	> Author: 杨玉春
	> Mail: www762268.@foxmail.come 
	> Created Time: 2016年08月29日 星期一 20时48分44秒
 ************************************************************************/

#if 0
#include <exynos_4412.h>
#include <led.h>
#include <key.h>
#include <pwm.h> 

/**********************************************************************
 * @brief		IRQ Interrupt Service Routine program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/


void do_irq(void )
{
	int irq_num;
	/*1.获取中断号*/
	irq_num = 0x3ff & CPU0.ICCIAR; 
	switch(irq_num)
	{
		case 42: //
			LED_ON(1);
			ICDICPR.ICDICPR1 |= 0x1 << 10;  //清除分配器标志位
		case 57: //KEY2

			key2_irq();
			break;
		case 58: //KEY3
			key3_irq();
			break;
	}
	/*CPU中断结束标志*/
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~0x3ff) | irq_num; 	
}

#endif

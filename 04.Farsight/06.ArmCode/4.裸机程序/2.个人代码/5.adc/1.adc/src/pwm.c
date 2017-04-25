/*************************************************************************
	> File Name: key.c
	> Author: 杨玉春
	> Mail: www762268.@foxmail.come 
	> Created Time: 2016年08月28日 星期日 20时38分10秒
 ************************************************************************/
#include <pwm.h> 

/*
 	GPD0_0 -- pwmTOUT0
 */
void PWM_Init()
{
	/**1.配置GPIO为TOUT_0输出*/
	GPD0.CON = (GPD0.CON & ~0xf) | 0x2;
	/*2.配置PWM频率*/
	PWM.TCFG0 = (PWM.TCFG0 & ~0xff) | 0xf9;
	PWM.TCFG1 = (PWM.TCFG1 & ~0xf) | 0x2;
	/*3.配置PWM占空比*/
	PWM.TCNTB0 = 200;
	PWM.TCMPB0 = 100;
	/*4.先置位(manual update),再清处并设置自动加载数据模式*/
	PWM.TCON = (PWM.TCON & ~0xf) | 0x2;
	PWM.TCON = (PWM.TCON & ~0xf) | 0x8;
}



void beep_on()
{
	PWM.TCON |= 0x1;
}


void beep_off()
{	
	PWM.TCON &= ~0x1;
}

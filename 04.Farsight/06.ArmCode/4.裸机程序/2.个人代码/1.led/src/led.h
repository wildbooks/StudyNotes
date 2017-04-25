/*************************************************************************
	> File Name: led.h
	> Author: 杨玉春
	> Mail: www762268.@foxmail.come 
	> Created Time: 2016年08月28日 星期日 21时50分32秒
 ************************************************************************/
#ifndef __LED__H
#define __LED__H

/*
 	1.LED2 -- LED5
		GPX2_7	GPX1_0	GPF3_4	GPF3_5
*/
#include <exynos_4412.h>

void LED_Init();
void LED_ON(int led);
void LED_OFF(int led);


#endif

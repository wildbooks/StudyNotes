/*************************************************************************
	> File Name: key.c
	> Author: 杨玉春
	> Mail: www762268.@foxmail.come 
	> Created Time: 2016年08月28日 星期日 20时38分10秒
 ************************************************************************/
#include <adc.h> 
#include <led.h>
/*
 	本程序使用的是当用户想ADC转化时才转化，这样可以降低功耗	
 */
void ADC_Init()
{ 
	/*1.选择通用ADC*/
	ADC_CFG &= ~(0X1 << 16);
	/*2.选择ADC通道位AIN3*/
	ADCMUX = 0x3;
	/*12bit enable 分频 Normal*/
	ADCCON = (ADCCON & 0x0) | ((1 << 16) | (1 << 14) | (0xff << 6));
}


/*轮询方式*/
int GetADCConverterData()
{
	int tmp;
	/*转化*/
	//ADCCON |= 1<<1; 
	ADCCON |= 0X1;
	/*判断转化是否结束*/
	while(!(ADCCON&(0X1 << 15)));
	tmp = ADCDAT & 0xfff;
	return tmp;
}

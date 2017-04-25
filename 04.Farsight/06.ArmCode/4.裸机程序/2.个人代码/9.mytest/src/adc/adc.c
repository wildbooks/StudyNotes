/*************************************************************************
	> File Name: key.c
	> Author: 杨玉春
	> Mail: www762268.@foxmail.come 
	> Created Time: 2016年08月28日 星期日 20时38分10秒
 ************************************************************************/
#include <adc.h> 
#include <led.h>
#include <uart.h>
/*
 	本程序使用的是当用户想ADC转化时才转化，这样可以降低功耗	
	中断号42 -- 集连号intG10_3
 */
void ADC_Init()
{ 
	/*1.选择通用ADC*/
	ADC_CFG &= ~(0X1 << 16);
	/*2.选择ADC通道位AIN3*/
	ADCMUX = 0x3;
	/*12bit enable 分频 Normal*/
	ADCCON = (ADCCON & 0x0) | ((1 << 16) | (1 << 14) | (0xff << 6));

	/*GIC*/ 
	ICDDCR = 1;	
	ICDISER.ICDISER1 |= 1 << 10;	
	ICDIPTR.ICDIPTR10 |= (ICDIPTR.ICDIPTR10 & ~(0xf <<16)) | 0X1 << 16;	
	/*Interrupt Combiner*/
	INTCOMBINER.IESR2 |= 1 << 19; //开启集连中断相关接口
	/*CPU接口*/
	CPU0.ICCICR = 1;
	CPU0.ICCPMR = 0xff;
}




/*中断方式*/
int GetADCConverterData()
{
	int tmp;
	if(INTCOMBINER.ISTR2 << 19)
	{
		tmp = ADCDAT & 0xfff;
		printf("tmp = %d\n", tmp);

		INTADCCLR = 1;   //清除ADC中断
	}
}

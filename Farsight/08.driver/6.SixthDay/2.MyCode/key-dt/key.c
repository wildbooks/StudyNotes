/*************************************************************************
	> File Name: key.c
	> Author: 杨玉春
	> Mail: www762268.@foxmail.come 
	> Created Time: 2016年08月28日 星期日 20时38分10秒
 ************************************************************************/
/*
	1.设置GPIO
		1.设置引脚为中断模式  GPX1CON
		2.禁止内部上下拉      GPX1PUD
		3.设置中断触发方式    EXT_INT41_CON
		4.相应引脚中断使能    EXT_INT41_MASK
		5.中断状态寄存器      EXT_INT41_PEND
			中断完成后需要清除相应位
		6.中断滤波            EXT_INT41_FLTCON0
	2.设置分配器
		1.使能分配器 ICDDCR = 1
		2.使能相应中断到分配器中 ICDISER.ICDISER1
		3.设置SPI25/SPI26由哪个cpu处理,当前设置cpu0
			ICDIPTR.ICDIPTR14
	3.选择CPU接口
		2.全局使能cpu0中断处理 CPU0.ICCICR 
		3.优先级屏蔽寄存器，设置CPU0能处理所有的中断
			CPU0.ICCPMR = 0xff
	4.中断处理函数
		获取中断号irq_num = (CPU0.ICCIAR & 0x3FF)  
	4.清除中断状态位
		1.外设级：EXT_INT41_PEND
		2.GIC级：ICDICPR.ICDICPR1
		3.CPU级：CPU0。ICCEOIR
*/
#include <key.h>
#include<led.h>

/*
	UART_RING -- EINT9 -- GPX1_1 -- K2 -- 57
	SIM_DET -- EINT10 -- GPX1_2 -- K3 -- 58
*/

void key_init()
{
	/****** GPIO配置 *********/
	/*1.设置GPIO为中断模式*/	
	GPX1.CON = (GPX1.CON & ~(0xff << 4)) | (0xff << 4);
	/*2.禁止上下拉*/
	GPX1.PUD &=  ~(0xf << 2);
	/*3.设置GPIO中断类型为双边沿触发*/
	//EXT_INT41_CON = (EXT_INT41_CON & ~((0x7 << 4) | (0x7 << 8))) | ((0x4 << 4) | (0x4 << 8));
	EXT_INT41_CON = (EXT_INT41_CON & ~(0x77 << 4)) | (0x22 << 4);
	/*4.开启中断滤波*/
	//EXT_INT41_FLTCON0 
	/*5.开启GPIO相应引脚中断*/
	EXT_INT41_MASK &= ~(0x3 << 1);

	/****** GIC配置 *********/
	/*1.开启中断分配器*/
	ICDDCR = 1; 
	/*2.开启相应中断分配器*/
	ICDISER.ICDISER1 |= (0x1 << 25) | (0x1 << 26);
	/*3.选择CPU处理器*/
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & ~(0xffff << 8)) | (0x0101<<8);
	/***** CPU接口配置 ******/
	/*1.开启CPU总中断*/
	CPU0.ICCICR = 1;
	/*2.CPU接受所有中断*/
	CPU0.ICCPMR = 0xff;
}

void key2_irq()
{
	/*中断处理函数*/
	LED_ON(0);
	LED_OFF(1);

	/*清除中断状态位*/
	EXT_INT41_PEND |= 0x1 << 1;     //置1清除标志位 
	ICDICPR.ICDICPR1 |= 0x1 << 25;  //清除分配器标志位
}



void key3_irq()
{

	/*中断处理函数*/
	LED_OFF(0);
	LED_ON(1);

	/*清除中断状态位*/
	EXT_INT41_PEND |= 0x1 << 2;     //置1清除标志位 
	ICDICPR.ICDICPR1 |= 0x1 << 26;  //清除分配器标志位
}

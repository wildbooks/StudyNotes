/*************************************************************************
	> File Name: led.c
	> Author: 杨玉春
	> Mail: www762268.@foxmail.come 
	> Created Time: 2016年08月28日 星期日 21时50分32秒
 ************************************************************************/
#include<led.h>

void LED_Init()
{	
	GPX2.CON = (GPX2.CON & ~(0xf << 28)) | (0x1 << 28);
	GPX1.CON = (GPX1.CON & ~0xf) | 0x1;
	GPF3.CON = (GPF3.CON & ~(0xff << 16)) | (0x11 << 16);
	GPX2.DAT &= ~(0x1 << 7);
	GPX1.DAT &= ~0x1;
	GPF3.DAT &= ~(0x3 << 4);
}
void LED_ON(int led)
{
	switch(led)
	{
		case 0:
			GPX2.DAT |= 0x1 << 7;
			break;
		case 1:
			GPX1.DAT |= 0x1;
			break;

		case 2:
			GPF3.DAT |= 0x1 << 4;
			break;
		case 3:
			GPF3.DAT |= 0x1 << 5;
			break;
		default:
			break;
	}
}
void LED_OFF(int led)
{
	switch(led)
	{
		case 0:
			GPX2.DAT &= ~(0x1 << 7);
			break;
		case 1:
			GPX1.DAT &= ~0x1;
			break;
		case 2:
			GPF3.DAT &= ~(0x1 << 4);
			break;
		case 3:
			GPF3.DAT &= ~(0x1 << 5);
			break;
		default:
			break;
	}
}

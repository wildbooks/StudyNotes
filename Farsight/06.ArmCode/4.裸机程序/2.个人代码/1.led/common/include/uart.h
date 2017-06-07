/*************************************************************************
	> File Name: uart.h
	> Author: 杨玉春
	> Mail: www762268.@foxmail.come 
	> Created Time: 2016年08月28日 星期日 21时50分32秒
 ************************************************************************/
#ifndef __UART__H
#define __UART__H

/*
*/
#include <exynos_4412.h>

void UART_Init();
char getchar();
void gets(char *pstr);
void putchar(const char data); 
void puts(const char *pstr);


void printf (const char *fmt, ...); 
#endif

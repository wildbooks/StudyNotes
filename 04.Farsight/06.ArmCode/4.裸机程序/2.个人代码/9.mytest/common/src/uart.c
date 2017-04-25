/*************************************************************************
	> File Name: key.c
	> Author: 杨玉春
	> Mail: www762268.@foxmail.come 
	> Created Time: 2016年08月28日 星期日 20时38分10秒
 ************************************************************************/
#include <uart.h> 

/*
 	COM7 -- UART2
		UART_AUDIO_RXD -- GPA1_0
		UART_AUDIO_TXD -- GPA1_1
	查询模式
		
 */
void UART_Init()
{
	/*1.GPIO配置*/
	GPA1.CON = (GPA1.CON & ~0xff) | 0x22; //UART2模式
	GPA1.PUD &= ~0xf; //禁止上下拉
	 
	/*2.UART配置*/
	//Normal mode, No parity, one stop,
	UART2.ULCON2 |= 0x3;
	//波特率 115200
	UART2.UBRDIV2 = 0x35;
	//UART2.UFRACVAL2 = 0x4;
	UART2.UFRACVAL2 = 0x5;
	//interrupt request or polling mode
	UART2.UCON2 = 0x5;  
}

char getchar()
{
	char data;
	while(!(UART2.UTRSTAT2&0x1)); //等待接收缓冲器有数据
	data = UART2.URXH2;
	if(data == '\r')
		data = '\n';
	return data;
}
/*
 	'\n' 是换行
	'\r' 行首
 
 */
void gets(char *pstr)
{
	
	while((*pstr = getchar()) != '\n')
	{
		putchar(*pstr);
		pstr++;
	}
	putchar(*pstr);
	*(++pstr) = 0;
}


void putchar(const char data)
{ 
	while(!(UART2.UTRSTAT2 & 0x2)); //等待发送缓冲器为空
	UART2.UTXH2 = data;
	if(data == '\n')
		putchar('\r');
}
void puts(const char *pstr)
{
	while(*pstr)	 //不为'\0'
		putchar(*pstr++);
}




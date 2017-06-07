/*
 * led_main.c
 *
 *  Created on: 2014-9-1
 *      Author: Administrator
 */


#define GPF3CON (*(volatile unsigned int *)0x114001e0)
#define GPF3DAT (*(volatile unsigned int *)0x114001e4)

#define GPX2CON (*(volatile unsigned int *)0x11000c40)
#define GPX2DAT (*(volatile unsigned int *)0x11000c44)
/*
 * 软件延时 延时值：loops
 */
void delay(unsigned int loops)
{
	while (loops > 0)
		loops--;
}

/*
 * 点亮某一个灯  number：第几个灯
 */
void led_num_on(unsigned int number)
{
	GPF3CON = GPF3CON & ~(0xff00ffff) | 0x00110000;


}

/*
 * 点灯
 */
void led_on(void)
{
	GPF3CON = GPF3CON & ~(0xff00ffff) | 0x00110000;
	GPF3DAT = 0x30;
}
/*
 * 灭灯
 */
void led_off(void)
{
	GPF3CON = GPF3CON & ~(0xff00ffff) | 0x00110000;
	GPF3DAT = 0x0;
}
/*
 * led灯主函数
 */
void led_main(void)
{

	GPF3CON = GPF3CON & ~(0xff00ffff) | 0x00110000;
	GPX2CON = GPX2CON & ~(0x0fffffff) | 0x10000000;
	GPX2DAT = 0x0;
	while (1) {
		led_on();
		delay(0x100000);
		led_off();
		delay(0x100000);

	}
}

/*
 *@brief	This example describes how to use General Interrupt Controller
 *@date:	02. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/
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
	3.选择CPU接口
		1.设置SPI25/SPI26由哪个cpu处理,当前设置cpu0
			ICDIPTR.ICDIPTR14
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





#include "exynos_4412.h"
void mydelay_ms(int ms);
extern void mystrcopy(char *d,const char *s);

static int num = 0;

/**********************************************************************
 * @brief		IRQ Interrupt Service Routine program body
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void do_irq(void )
{
	int irq_num; char dat;
	irq_num = (CPU0.ICCIAR & 0x1FF);
	unsigned int value;

	__asm__ __volatile__("mrs %[tmp], cpsr": [tmp]"=r"(value)::"memory");
	printf("***in int isr****cpsr = 0x%x \r\n", value);
	__asm__ __volatile__(
	"mrs %0,cpsr"
	:"=r"(value)
	:
	:"memory"
	);
	printf("***in int*** isr****cpsr = 0x%x \r\n", value);
	switch (irq_num) {

	case 58: //turn on LED2; turn off LED3
		GPX2.GPX2DAT = 0x1 << 7;
		GPX1.GPX1DAT &= ~0x1;
		printf("IRQ interrupt !! turn on LED2; turn off LED3\n");
		dat = GPX1.GPX1DAT & 0x1;
		mydelay_ms(10);
		if(dat==(GPX1.GPX1DAT & 0x1))
			printf("IRQ interrupt !!key1 pressed\n");

		//Clear Pend
		EXT_INT41_PEND |= 0x1 << 2;   //GPIO发生中断状态的标志被清除
		ICDICPR.ICDICPR1 |= 0x1 << 26;
		break;
	case 57: //Turn on Led3; Turn off Led2

		GPX2.GPX2DAT &= ~(0x1 << 7);
		GPX1.GPX1DAT |= 0x1;
		printf("IRQ interrupt !! Turn on LED3; Turn off LED2\n");
		dat = GPX1.GPX1DAT & 0x1<<1;
		mydelay_ms(10);
		if(dat==(GPX1.GPX1DAT & 0x1<<1))
			printf("IRQ interrupt !!key2 pressed\n");
		//Clear Pend
  		EXT_INT41_PEND |= 0x1 << 1;
		ICDICPR.ICDICPR1 |= 0x1 << 26;
		break;
	}

	// End of interrupt
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~(0x1FF)) | irq_num;

}

/**********************************************************************
 * @brief		mydelay_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void mydelay_ms(int ms)
{
	int i, j;
	while(ms--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}


/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void)
{
	unsigned int value;
	__asm__ __volatile__("mrs %0, cpsr": "=r"(value));
	printf("***in main****cpsr = 0x%x \r\n", value);
	const char *src ="hello c call asm func: mystrcopy()";
	char dest[20]={};

	mystrcopy(dest,src);
	printf("copy by asm func,%s\r\n",dest);

	//LED2 GPX2_7
 	GPX2.GPX2CON |= 0x1 << 28;
	//LED3 GPX1_0
	GPX1.GPX1CON |= 0x1;
	//Led4 GPF3_4
	GPF3.GPF3CON |= 0x1 << 16;

	//Key_2  Interrupt  GPX1_1
	GPX1.GPX1PUD = GPX1.GPX1PUD & ~(0x3 << 2); // Disables Pull-up/Pull-down
	GPX1.GPX1CON = (GPX1.GPX1CON & ~(0xF << 4)) | (0xF << 4); //GPX1_1: WAKEUP_INT1[1](EXT_INT41[1]) EXT_INT41_CON = (EXT_INT41_CON & ~(0x7 << 4)) | 0x2 << 4;
	EXT_INT41_MASK = (EXT_INT41_MASK & ~(0x1 << 1)); //  Bit: 1 = Enables interrupt

	//Key_3  Interrupt  GPX1_2
	GPX1.GPX1PUD = GPX1.GPX1PUD & ~(0x3 << 4); // Disables Pull-up/Pull-down
	GPX1.GPX1CON = (GPX1.GPX1CON & ~(0xF << 8)) | (0xF << 8); //GPX1_2:WAKEUP_INT1[2] (EXT_INT41[2])
	EXT_INT41_CON = (EXT_INT41_CON & ~(0x7 << 8)) | 0x2 << 8; //下降沿触发
	EXT_INT41_MASK = (EXT_INT41_MASK & ~(0x1 << 2)); //  Bit: 1 = Enables interrupt


	/*
	 * GIC interrupt controller:
	 **/

	//使能分配器
	ICDDCR = 1; 	//Bit1:  GIC monitors the peripheral interrupt signals and
					//		forwards pending interrupts to the CPU interfaces2
	
	//使能相应中断到分配器中
	// Enables the corresponding interrupt SPI25, SPI26 -- Key_2, Key_3
	// key2-EINT9-GPX1_1-57
	// key3-EINT10-GPX1_2-58
	ICDISER.ICDISER1 |= (0x1 << 25) | (0x1 << 26); //中断号57%32=25，58%32=26 开启相应引脚中断

	//选择CPU接口
	//ICDIPTR.ICDIPTR14 = 0x01010101;	//SPI25  SPI26  interrupts are sent to processor 0   
	ICDIPTR.ICDIPTR14 = 0x0101;	//SPI25  SPI26  interrupts are sent to processor 0   

	//为什么用CUP0开启总中断？因为只有CPU0支持SPI中断
	CPU0.ICCICR |= 0x1; //Global enable for signaling of interrupts cpu0打开总中断,

	/*优先级屏蔽寄存器，设置cpu0能处理所有中断*/
	CPU0.ICCPMR = 0xFF; //The priority mask level.Priority filter. threshold 中断最低优先级



	printf("\n ********* GIC test ********\n");

	while (1){
		GPF3.GPF3DAT |= 0x1 << 4;
		mydelay_ms(500);
		GPF3.GPF3DAT &= ~(0x1 << 4);
		mydelay_ms(500);
	}

	return 0;
}

/*
 *@brief	This example describes how to use SPI
 *@date:	12. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"
#include "uart.h"

/*
 * Irq_rutine
 * */
void do_irq() {

}

/**********************************************************************
 * @brief		mydelay_ms_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void mydelay_ms(int time)
{
	int i, j;
	while(time--)
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
	unsigned char data = 0;

	GPX2.CON = 0x1 << 28;
	uart_init();

	GPC1.CON = (GPC1.CON & ~0xffff0) | 0x55550;//设置IO引脚为SPI模式

	/*spi clock config*/
	CLK_SRC_PERIL1 = (CLK_SRC_PERIL1 & ~(0xF<<24)) | 6<<24;// 0x6: 0110 = SCLKMPLL_USER_T 800Mhz
	CLK_DIV_PERIL2 = 19 <<8 | 3;//SPI_CLK = 800/(19+1)/(3+1)

	soft_reset();	                   // 软复位SPI控制器
	SPI2.CH_CFG &= ~( (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | 0x3);//master mode, CPOL = 0, CPHA = 0 (Format A)
	SPI2.MODE_CFG &= ~((0x3 << 17) | (0x3 << 29));   //BUS_WIDTH=8bit,CH_WIDTH=8bit
	SPI2.CS_REG &= ~(0x1 << 1);        //选择手动选择芯片
    delay(10);    //延时

    printf("\n***************** SPI test!! ******************\n");
    while(1)
    {
    	reset_2515(); //复位
    	mydelay_ms(10);
		printf("spi send '0x80' to 2515......\n");
		write_byte_2515(0x0f, 0x80); //CANCTRL寄存器－－进入配置模式 中文DATASHEET 58页
		mydelay_ms(10);
		data = read_byte_2515(0x0f);
		printf("spi receive a byte : 0x%0x\n", data);
		mydelay_ms(1000);
    }

	return 0;
} //main

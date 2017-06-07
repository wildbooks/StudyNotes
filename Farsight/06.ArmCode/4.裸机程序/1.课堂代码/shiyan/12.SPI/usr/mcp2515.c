#include "mcp2515.h"
#include "exynos_4412.h"

void delay(int times)
{
	volatile int i,j;
	for (j = 0; j < times; j++)
	{
		for (i = 0; i < 1000; i++);
	}
}
/*
 * 片选从机
 */
void slave_enable(void)
{

	SPI2.CS_REG &= ~0x1; //enable salve
	delay(3);
}
/*
 * 取消片选从机
 */
void slave_disable(void)
{

	SPI2.CS_REG |= 0x1; //disable salve
	delay(1);
}
/*
 * 功能：向SPI总线发送一个字节
 */
void send_byte(unsigned char data)
{
	SPI2.CH_CFG |= 0x1; // enable Tx Channel
	delay(1);
	SPI2.SPI_TX_DATA = data;
	while( !(SPI2.SPI_STATUS & (0x1 << 25)) );
	SPI2.CH_CFG &= ~0x1; // disable Tx Channel
}
/*
 * 功能：从SPI总线读取一个字节
 */
unsigned char recv_byte()
{
	unsigned char data;
	SPI2.CH_CFG |= 0x1 << 1; // enable Rx Channel
	delay(1);
	data = SPI2.SPI_RX_DATA;
	delay(1);
	SPI2.CH_CFG &= ~(0x1 << 1); //disable Rx Channel
	return  data;
}
/*
 * 复位spi控制器
 */
void soft_reset(void)
{
	SPI2.CH_CFG |= 0x1 << 5;
	delay(1);                     //延时
	SPI2.CH_CFG &= ~(0x1 << 5);
}

//功能：复位指令可以重新初始化MCP2515 的内部寄存器，并设置配置模式
void reset_2515()
{
	soft_reset();      //复位spi控制器
    slave_enable() ;   //片选从机
	send_byte(0xc0);   //发送复位命令
	slave_disable() ;  //取消片选

}
//功能：请求发送命令
void send_req_2515()
{
 //   CS_SPI = 0; //复位
	soft_reset();      //复位spi控制器
    slave_enable() ;   //片选从机
	send_byte(0x81);   //发送请求命令
	slave_disable() ;  //取消片选
//	CS_SPI=1;
}
//功能：只修改寄存器中的某些位
//入口参数：Addr:寄丰器地址  MASK：屏蔽字  为1时可以对当前位修改  dat:数据字节
void bit_modify_2515(unsigned char addr, unsigned char mask, unsigned char data)
{
//    CS_SPI = 0 ;
    slave_enable() ;
    send_byte(0x05) ;
    send_byte(addr) ;
    send_byte(mask) ;
    send_byte(data) ;
    slave_disable() ;
//    CS_SPI = 1 ;
}

/*
 * 功能：从指定地址起始的寄存器读取数据。
 *unsigned char Addr 要读取地址寄存器的地址
 *返回值：从地址当中读取的数值
 */
unsigned char read_byte_2515(unsigned char Addr)
{
	unsigned char ret;
//    CS_SPI = 0;
    slave_enable();
    send_byte(0x03);
    send_byte(Addr);
    ret = recv_byte();
    slave_disable();
//    CS_SPI = 1;
    return(ret);
}

/*
 * 功能：将数据写入指定地址起始的寄存器。
 * unsigned char addr 寄存器的地址
 * unsigned char data 向寄存器写入的数据
 */
void write_byte_2515(unsigned char addr,unsigned char data)
{
    slave_enable();
    send_byte(0x02);
    send_byte(addr);
    send_byte(data);
    slave_disable();
}

void  Init_can(void)
{
//unsigned char ret;
    reset_2515(); //复位
    write_byte_2515(0x0f, 0x80);     //CANCTRL寄存器－－进入配置模式 中文DATASHEET 58页

	//可以设置的波特率 5K 10K 15K 20K 25K 40K 50K 80K 100K 125K 200K 400K 500K 667K 800K 1M
    write_byte_2515(0x2A, CNF1_20K); //CNF1位定时配置寄器   中文DATASHEET 41-42页
    write_byte_2515(0x29, CNF2_20K); //CNF2位定时配置寄器   中文DATASHEET 41-42页
    write_byte_2515(0x28, CNF3_20K); //CNF3位定时配置寄器   中文DATASHEET 41-43页
    write_byte_2515(0x2B, 0x1f);     //CANINTE中断使能寄存器  中文DATASHEET 50 页
    write_byte_2515(0x60, 0x60);     //RXB0CTRL接收缓冲器0 控制寄存器 中文DATASHEET 27 页
    //write_byte_2515(0x70, 0x20);   //接收缓冲器1控制寄存器
    bit_modify_2515(0x0C, 0x0f, 0x0f); //BFPCTRL_RXnBF 引脚控制寄存器和状态寄存器 中文DATASHEET 29 页

    write_byte_2515(0x0f, 0x40);   //CAN控制寄存器－－回环模式,用于测试
}

/*
 * tx_buff[]
 * Fream 数据帧的类型
 */
void Can_send(unsigned char *tx_buff)
{
	unsigned char i;
	write_byte_2515(0x30, 0x03); //设置为发送最高优先级
	write_byte_2515(0x31, 0xff); //发送缓冲器0标准标识符高位
	write_byte_2515(0x32, 0x00); //发送缓冲器0标准标识符低位
	write_byte_2515(0x35, 0x08);  //发送缓冲器0数据长度码8字节
	for(i = 0; i < 8; i++)
	{
		write_byte_2515(0x36+i ,tx_buff[i]); //向txb缓冲器中写入8个字节
//		printf("%x ",tx_buff[i]);
	}
	send_req_2515();

}

unsigned char Can_receive(unsigned char *rx_buff)
{
	unsigned char i,flag;
    flag = read_byte_2515(0x2c); //CANINTF——中断标志寄存器
    printf("flag=%x\n",flag);
  //  printf(" SPI2.SPI_STATUS =%x\n", SPI2.SPI_STATUS );
 //   soft_reset();
    if (flag&0x1)                //接收缓冲器0满中断标志位
    {
    	for(i = 0; i < 16; i++)
		{
    		rx_buff[i]= read_byte_2515(0x60+i);
    //		printf("%x ",rx_buff[i]);
    //		printf(" SPI2.SPI_STATUS =%x\n", SPI2.SPI_STATUS );
    		soft_reset();
		}
    	bit_modify_2515(0x2c,0x01,0x00);
    	write_byte_2515(0x2c, 0x00);
		if (!(rx_buff[1]&0x08)) return(1);	  //接收标准数据帧
    }
    return(0);
}


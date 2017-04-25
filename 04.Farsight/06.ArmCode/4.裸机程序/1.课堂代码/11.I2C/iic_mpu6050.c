//****************************************                                                                                         
//  MPU6050内部地址                                                                                                                
//****************************************                                                                                         
#define SMPLRT_DIV      0x19    //陀螺仪采样率，典型值：0x07(125Hz)                                                                
#define CONFIG          0x1A    //低通滤波频率，典型值：0x06(5Hz)                                                                  
#define GYRO_CONFIG     0x1B    //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)                                            
#define ACCEL_CONFIG    0x1C    //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)                                
#define ACCEL_XOUT_H    0x3B                                                                                                       
#define ACCEL_XOUT_L    0x3C                                                                                                       
#define ACCEL_YOUT_H    0x3D                                                                                                       
#define ACCEL_YOUT_L    0x3E                                                                                                       
#define ACCEL_ZOUT_H    0x3F                                                                                                       
#define ACCEL_ZOUT_L    0x40                                                                                                       
#define TEMP_OUT_H      0x41                                                                                                       
#define TEMP_OUT_L      0x42                                                                                                       
#define GYRO_XOUT_H     0x43                                                                                                       
#define GYRO_XOUT_L     0x44                                                                                                       
#define GYRO_YOUT_H     0x45                                                                                                       
#define GYRO_YOUT_L     0x46                                                                                                       
#define GYRO_ZOUT_H     0x47                                                                                                       
#define GYRO_ZOUT_L     0x48                                                                                                       
#define PWR_MGMT_1      0x6B    //电源管理，典型值：0x00(正常启用)                                                                 
#define WHO_AM_I        0x75    //IIC地址寄存器(默认数值0x68，只读)                                                                
#define SlaveAddress    0xD0    //IIC写入时的地址字节数据，+1为读取                                                                
void mydelay_ms(int time)                                                                                                          
{                                                                                                                                  
    int i, j;                                                                                                                      
    while(time--)                                                                                                                  
    {                                                                                                                              
        for (i = 0; i < 5; i++)                                                                                                    
            for (j = 0; j < 514; j++);                                                                                             
    }                                                                                                                              
}                                                                                                                                  
/**********************************************************************                                                            
 * @brief       iic read a byte program body                                                                                       
 * @param[in]   slave_addr, addr, &data                                                                                            
 * @return      None                                                                                                               
 **********************************************************************/                                                           
void iic_read(unsigned char slave_addr, unsigned char addr, unsigned char *data)                                                   
{                                                                                                                                  
    I2C5.I2CDS = slave_addr; //将从机地址写入I2CDS寄存器中                                                                         
    I2C5.I2CCON = (1 << 7)|(1 << 6)|(1 << 5); //设置时钟并使能中断                                                                 
    I2C5.I2CSTAT = 0xf0; //[7:6]设置为0b11，主机发送模式；                                                                         
                         //往[5：4]位写0b11，即产生启动信号,发出IICDS寄存器中的地址                                                
    while(!(I2C5.I2CCON & (1 << 4))); // 等待传输结束，传输结束后，I2CCON [4]位为1，标识有中断发生；                               
                                      // 此位为1时，SCL线被拉低，此时I2C传输停止；                                                 
    I2C5.I2CDS = addr; //写命令值                                                                                                  
    I2C5.I2CCON = I2C5.I2CCON & (~(1 << 4)); // I2CCON [4]位清0，继续传输                                                          
    while(!(I2C5.I2CCON & (1 << 4))); // 等待传输结束                                                                              
    I2C5.I2CSTAT = 0xD0; // I2CSTAT[5:4]位写0b01,发出停止信号                                                                      
                                                                                                                                   
    I2C5.I2CDS = slave_addr | 1; //表示要读出数据                                                                                  
    I2C5.I2CCON = (1 << 7)|(1 << 6) |(1 << 5) ; //设置时钟并使能中断                                                               
    I2C5.I2CSTAT = 0xb0; //[7:6]位0b10,主机接收模式；                                                                              
                         //往[5：4]位写0b11，即产生启动信号,发出IICDS寄存器中的地址                                                
    //I2C5.I2CCON = I2C5.I2CCON & (~(1 << 4));                                                                                     
    while(!(I2C5.I2CCON & (1 << 4))); //等待传输结束，接收数据                                                                     
                                                                                                                                   
    I2C5.I2CCON &= ~((1<<7)|(1 << 4)); // I2CCON [4]位清0，继续传输，接收数据，                                                    
                                       // 主机接收器接收到最后一字节数据后，不发出应答信号 no ack                                  
                                       // 从机发送器释放SDA线，以允许主机发出P信号，停止传输；                                     
    while(!(I2C5.I2CCON & (1 << 4)));  // 等待传输结束                                                                             
    *data = I2C5.I2CDS;                                                                                                            
    I2C5.I2CSTAT = 0x90;                                                                                                           
    I2C5.I2CCON &= ~(1<<4);       /*clean interrupt pending bit  */                                                                
                                                                                                                                   
}                                                                                                                                  
/**********************************************************************                                                            
 * @brief       iic write a byte program body                                                                                      
 * @param[in]   slave_addr, addr, data                                                                                             
 * @return      None                                                                                                               
 **********************************************************************/                                                           
void iic_write (unsigned char slave_addr, unsigned char addr, unsigned char data)                                                  
{                                                                                                                                  
    I2C5.I2CDS = slave_addr;                                                                                                       
    I2C5.I2CCON = (1 << 7)|(1 << 6)|(1 << 5) ;                                                                                     
    I2C5.I2CSTAT = 0xf0;                                                                                                           
    while(!(I2C5.I2CCON & (1 << 4)));                                                                                              
                                                                                                                                   
    I2C5.I2CDS = addr;                                                                                                             
    I2C5.I2CCON = I2C5.I2CCON & (~(1 << 4));                                                                                       
    while(!(I2C5.I2CCON & (1 << 4)));                                                                                              
                                                                                                                                   
    I2C5.I2CDS = data;                                                                                                             
    I2C5.I2CCON = I2C5.I2CCON & (~(1 << 4));                                                                                       
    while(!(I2C5.I2CCON & (1 << 4)));                                                                                              
                                                                                                                                   
    I2C5.I2CSTAT = 0xd0;                                                                                                           
    I2C5.I2CCON = I2C5.I2CCON & (~(1 << 4));                                                                                       
    mydelay_ms(10);                                                                                                                
                                                                                                                                   
}                                                                                                                                  
                                                                                                                                   
void MPU6050_Init ()                                                                                                               
{                                                                                                                                  
	    iic_write(SlaveAddress, PWR_MGMT_1, 0x00);                                                                                   
	    iic_write(SlaveAddress, SMPLRT_DIV, 0x07);                                                                                   
	    iic_write(SlaveAddress, CONFIG, 0x06);                                                                                       
	    iic_write(SlaveAddress, GYRO_CONFIG, 0x18);                                                                                  
	    iic_write(SlaveAddress, ACCEL_CONFIG, 0x01);                                                                                 
	}                                                                                                                                
	int get_data(unsigned char addr)                                                                                                 
	{                                                                                                                                
	    char data_h, data_l;                                                                                                         
	    iic_read(SlaveAddress, addr, &data_h);                                                                                       
	    iic_read(SlaveAddress, addr+1, &data_l);                                                                                     
	    return (data_h<<8)|data_l;                                                                                                   
	}                                                                                                                                
	                                                                                                                                 
	/*                                                                                                                               
	 *  裸机代码，不同于LINUX 应用层， 一定加循环控制                                                                                
	 */                                                                                                                              
	int main(void)                                                                                                                   
	{                                                                                                                                
	    int data;                                                                                                                    
	                                                                                                                                 
	    unsigned char zvalue;                                                                                                        
	    GPB.CON = (GPB.CON & ~(0xff<<8)) | 0x33<<8; // GPBCON[3], I2C_5_SCL GPBCON[2], I2C_5_SDA                                     
	    mydelay_ms(100);                                                                                                             
	    uart_init();                                                                                                                 
	                                                                                                                                 
	/*---------------------------------------------------------------------*/                                                        
	    I2C5.I2CSTAT = 0xD0;                                                                                                         
	    I2C5.I2CCON &= ~(1<<4);       /*clean interrupt pending bit  */                                                              
	/*---------------------------------------------------------------------*/                                                        
	                                                                                                                                 
	    mydelay_ms(100);                                                                                                             
	    MPU6050_Init();                                                                                                              
	    mydelay_ms(100);                                                                                                             
	                                                                                                                                 
	    printf("\n********** I2C test!! ***********\n");                                                                             
	                                                                                                                                 
	    while(1)                                                                                                                     
	    {                                                                                                                            
	        //Turn on                                                                                                                
	                                                                                                                                 
	        data = get_data(GYRO_ZOUT_H);                                                                                            
	        printf(" GYRO --> Z <---:Hex: %x", data);                                                                                
	        data = get_data(GYRO_XOUT_H);                                                                                            
	        printf(" GYRO --> X <---:Hex: %x", data);                                                                                
	        printf("\n");                                                                                                            
	        mydelay_ms(1000);                                                                                                        
	    }                                                                                                                            
	    return 0;                                                                                                                    
	}                                                                                                                                


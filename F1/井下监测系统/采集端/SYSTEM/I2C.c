#include <I2C.h>
#include <delay.h>
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
/***************************************************************************
名    称：void InitI2C0(void)
功    能：初始化IO口
入口参数：无
出口参数：无
说    明：
调用方法：InitI2C0();
***************************************************************************/
void InitI2C0(void)
{		
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOB时钟

  //GPIOB8,B9初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
	I2C_SCL0=1;
	I2C_SDA0=1;
}

/***************************************************************************
名    称：void StartI2C0(void)
功    能：启动I2C总线，即发送I2C初始条件
入口参数：无
出口参数：无
说    明：
调用方法：StartI2C0();
***************************************************************************/
void StartI2C0(void)
{
    I2C_SDA0=1;    
    delay_us(100);

    I2C_SCL0=1;	   
    delay_us(100);
 
    I2C_SDA0=0;
    delay_us(100);

    I2C_SCL0=0;	 
    delay_us(100);


}

/***************************************************************************
名    称：void StopI2C0(void)
功    能：结束I2C总线，即发送I2C结束条件
入口参数：无
出口参数：无
说    明：
调用方法：StopI2C0();
***************************************************************************/
void StopI2C0(void)
{
	I2C_SDA0=0;
    delay_us(100);
 
    I2C_SCL0=1;
    delay_us(100);  

    I2C_SDA0=1;
    delay_us(100);
 

}

/***************************************************************************
名    称：void NoAck0(void)
功    能：无应答
入口参数：无
出口参数：无
说    明：
调用方法：NoAck0();
***************************************************************************/
void NoAck0(void)
{
	
	I2C_SDA0=1;
	delay_us(100);
	
	I2C_SCL0=1;
	delay_us(100);
	
	I2C_SCL0=0;
	delay_us(100);
	
	I2C_SDA0=0;
	delay_us(100);

}
/***************************************************************************
名    称：void Ack0(void)
功    能：总线应答
入口参数：无
出口参数：无
说    明：
调用方法：Ack0();
***************************************************************************/
void Ack0(void)
{
	SDA_OUT0();
 	I2C_SDA0=1;
    delay_us(100); 
    I2C_SCL0=1;
    delay_us(100); 
	I2C_SCL0=0;
    delay_us(100); 
 	I2C_SDA0=1;

	
}
/***************************************************************************
名    称：unsigned char TestAck0( )
功    能：应答校验
入口参数：无
出口参数：应答状态
说    明：
调用方法：m=TestAck0();
***************************************************************************/
unsigned char TestAck0( )
{
	unsigned char ack;

	I2C_SCL0=1;
	delay_us(100);
	SDA_IN0();
	delay_us(100);
	ack=SDA_STATE0;
	delay_us(100);
	I2C_SCL0=0;
	delay_us(100);
	return(ack);


}
/***************************************************************************
名    称：unsigned char I2CWrite0(unsigned char DData)
功    能：向I2C总线上发送1字节数据
入口参数：DData    待发送数据
出口参数：无
说    明：
调用方法：NoAck0();
***************************************************************************/
unsigned char I2CWrite0(unsigned char DData)
{
	unsigned char j,tem;

	for(j=0;j<8;j++) 
	{
		if((DData<<j)&0x80)
		{
			I2C_SDA0=1;
		}
		else
		{
			I2C_SDA0=0;
		}
		delay_us(100);
		I2C_SCL0=1;
		delay_us(100);
		I2C_SCL0=0;;
		delay_us(100);

	}
	delay_us(100);
	
	SDA_IN0();
	delay_us(100);
	I2C_SCL0=1;
	delay_us(1000);
	if(SDA_STATE0==1)
	{
		tem=0;  
	}
	else
	{
		tem=1;   
	}
	I2C_SCL0=0;
	delay_us(100);	
    SDA_OUT0();

	return(tem);  
}

/***************************************************************************
名    称：unsigned char I2CRead0(void)
功    能：从I2C总线上接收1字节数据
入口参数：无
出口参数：接收数据
说    明：
调用方法：m=I2CRead0();
***************************************************************************/
unsigned char I2CRead0(void)
{
	unsigned char read,j;
	read=0x00;
	
	SDA_IN0();
	delay_us(100);
	for(j=8;j>0;j--) 
	{		     
		delay_us(100);
		I2C_SCL0=1;
		delay_us(100);
		read=read<<1;
		if(SDA_STATE0==1) 
		{
			read=read+1;
		}
		I2C_SCL0=0;
		delay_us(100);
	}	
	return(read);
}


/***************************************************************************
***************************************************************************/

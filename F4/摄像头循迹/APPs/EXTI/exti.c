#include "exti.h"
#include "delay.h" 
#include "ov7670.h"
#include "lcd.h"

u8 ov_sta;
 //外部中断5~9服务程序
void EXTI9_5_IRQHandler(void)
{	 		
	if(EXTI->PR&(1<<9))//是9线的中断
	{     
		if(ov_sta<2)
		{
			if(ov_sta==0)
			{
				OV7670_WRST=0;	 	//复位写指针	
				delay_us(1);
				OV7670_WRST=1;	
				OV7670_WREN=1;		//允许写入FIFO
			}else OV7670_WREN=0;	//禁止写入FIFO 	 
			ov_sta++;
		}	 
	}
	EXTI->PR=1<<9;     //清除LINE8上的中断标志位
} 
//外部中断9初始化
void EXTI9_Init(void)
{												  
	Ex_NVIC_Config(GPIO_F,9,RTIR); 			//任意边沿触发			  
	MY_NVIC_Init(0,0,EXTI9_5_IRQn,2);		//抢占0,子优先级0，组2	   
}













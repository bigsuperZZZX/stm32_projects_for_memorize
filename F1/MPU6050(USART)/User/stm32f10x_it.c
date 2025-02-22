/**
  ******************************************************************************
  * @file    GPIO/JTAG_Remap/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "sys.h"
#include "string.h"
//#include "uart_1.h"
//#include "dma.h"
//#include "RS485.h"
//#include "74hc595.h"

//u8 t = 0;	 //定义临时变量 测试用
//u8 he = 0;	//校验和
//
//extern u8 f;    //测试用,串口1准备发送标志
//
//#define led_PB13   PBout(13)	   //位绑定，位定义PB13口作为LED输出。这样速度最快
//#define feng      PBout(14)	   //位绑定，位定义PB14口作为LED输出(蜂鸣器)。这样速度最快
//
//#define CLK1   PDout(0)
//#define CWW1   PDout(1)
//#define CLK2   PDout(2)
//#define CWW2   PDout(3)
//
//u8 buff[5] = {0,0,0,0,0}; //测试
//u8 p = 0;  //测试
//u8 LR_uart_buf = 0;
//u8 UD_uart_buf = 0;
//u8 fang_xiang = 0;
//u8 Led_T = 0; //LED发光时间变量
////u8 Time2_OK = 0;  //定时器中断完成标志

unsigned char Re_buf[11],temp_buf[11],counter=0;
unsigned char sign,t,he;
static unsigned char Temp[11];



void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断有效,若接收数据寄存器满
     {
      Temp[counter] = USART_ReceiveData(USART2);   //接收数据
	  if(counter == 0 && Temp[0] != 0x55) return;      //第 0 号数据不是帧头，跳过
      counter++; 
      if(counter==11) //接收到 11 个数据
      { 
         memcpy(Re_buf,Temp,11);
         counter=0; //重新赋值，准备下一帧数据的接收
         sign=1;
      }
		 }
}





/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_JTAG_Remap
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void WWDG_IRQHandler(void)		 //窗口定时器中断服务函数
{
}

void PVD_IRQHandler(void)		 //联到EXTI的电源电压检测（PVD）中断服务函数
{
}

void TAMPER_IRQHandler(void)	 //侵入检测中断服务函数
{
}

void RTC_IRQHandler(void)		 //实时时钟（RTC）全局中断服务函数
{

}

void FLASH_IRQHandler(void)		 //闪存全局中断服务函数
{
}

void RCC_IRQHandler(void)		 //复位和时钟控制（RCC）中断服务函数
{
}

void EXTI0_IRQHandler(void)		 //EXTI线0中断服务函数
{

}

void EXTI1_IRQHandler(void)		 //EXTI线1中断服务函数
{

}

void EXTI2_IRQHandler(void)		 //EXTI线2中断服务函数
{
}

void EXTI3_IRQHandler(void)		 //EXTI线3中断服务函数
{
}

void EXTI4_IRQHandler(void)		 //EXTI线4中断服务函数
{
 
}

void DMA1_Channel1_IRQHandler(void)	   //DMA1通道1全局中断服务函数
{
}

void DMA1_Channel2_IRQHandler(void)	   //DMA1通道2全局中断服务函数
{
}

void DMA1_Channel3_IRQHandler(void)	   //DMA1通道3全局中断服务函数
{
}

void DMA1_Channel4_IRQHandler(void)	   //DMA1通道4全局中断服务函数
{
//	//判断是否为DMA发送完成中断
//	if(DMA_GetFlagStatus(DMA1_FLAG_TC4)==SET) 
//	{  	
//		DMA_ClearFlag(DMA2_FLAG_TC4);//清除通道4传输完成标志 
//	}	
}

void DMA1_Channel5_IRQHandler(void)	   //DMA1通道5全局中断服务函数
{
//	if(DMA_GetITStatus(DMA1_IT_TC5))
// 	{
//	    //DataCounter = DMA_GetCurrDataCounter(DMA1_Channel5);//获取剩余长度,一般都为0,调试用
//	    DMA_ClearITPendingBit(DMA1_IT_GL5);	//清除全部中断标志										     
//		//转换可操作BUF
//		if(Free_Buf_No==BUF_NO1) //如果BUF1空闲，将DMA接收数据赋值给BUF1
//		{	
//			DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf1;
//			DMA_Init(DMA1_Channel5, &DMA_InitStructure);
//			Free_Buf_No=BUF_NO2;
//		}
//		else  //如果BUF2空闲，将DMA接收数据赋值给BUF2
//		{
//			DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_DMA_Buf2;
//			DMA_Init(DMA1_Channel5, &DMA_InitStructure);
//			Free_Buf_No=BUF_NO1;
//		}
//		Buf_Ok=TRUE;	   //有准备好的数据了
// 	}
}

void DMA1_Channel6_IRQHandler(void)	   //DMA1通道6全局中断服务函数
{
}

void DMA1_Channel7_IRQHandler(void)	   //DMA1通道7全局中断服务函数
{
}

void ADC1_2_IRQHandler(void)		   //ADC全局中断服务函数
{
    //Get injected channel1 converted value  // ADC_GetConversionValue(ADC1);
 //     ADC_ConvertedValue = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
 //     ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC); // 清除ADCx的中断待处理位 ；

/*  GPIO_WriteBit(GPIOB,GPIO_Pin_8,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8)));
    ADC_ClearITPendingBit(ADC1, ADC_IT_AWD); // 清除ADC1的AWDOG中断屏蔽处理位 ；    */

    /* Clear ADC1 JEOC pending interrupt bit */
  //    ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
  //    ADC_ConvertedValue = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
}

void USB_HP_CAN_TX_IRQHandler(void)	   //USB高优先级或CAN发送中断服务函数
{
}

void USB_LP_CAN_RX0_IRQHandler(void)   //USB低优先级或CAN接收0中断服务函数
{
}

void CAN_RX1_IRQHandler(void)		   //CAN接收1中断服务函数
{
}

void CAN_SCE_IRQHandler(void)		   //CAN SCE中断服务函数
{
}

void EXTI9_5_IRQHandler(void)		   //外部中断9线【9:5】中断服务函数
{
//	if(EXTI_GetITStatus(EXTI_Line9) != RESET) 
//	{
//     //添加中断处理程序
////		t = !t;	   //取反标志位
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //一个位操作PB1口输出低电平点亮LED灯
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // 一个位操作 PB1口输出高电平关闭LED灯
//
//		led_PB13 = ~led_PB13;	   //取反
//	
//		EXTI_ClearFlag(EXTI_Line9);			          //清除中断标志（必须）
//		EXTI_ClearITPendingBit(EXTI_Line9);			  //清除中断挂起�
//	 }
}

void TIM1_BRK_IRQHandler(void)		   //定时器1断开中断服务函数
{
}

void TIM1_UP_IRQHandler(void)		   //定时器1更新中断服务函数
{
}

void TIM1_TRG_COM_IRQHandler(void)	   //定时器1触发和通信中断服务函数
{
}

void TIM1_CC_IRQHandler(void)		   //定时器1捕获比较中断服务函数
{
}

void TIM2_IRQHandler(void)			   //定时器2全局中断服务函数
{
//	if(TIM2->SR & 0X0001)//溢出中断
//	{	
//	    //添加中断处理程序
////		t = !t;	   //取反标志位
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //一个位操作PB1口输出低电平点亮LED灯
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // 一个位操作 PB1口输出高电平关闭LED灯
//		
//		CLK1 = ~CLK1;
//	}				   
//	TIM2->SR &= ~(1<<0);//清除中断标志位
//	TIM_Cmd(TIM2, DISABLE);						 //关定时器2，在main函数内打开
//	
//	//Time2_OK = 1;
}

void TIM3_IRQHandler(void)			   //定时器3全局中断服务函数
{
//	if(TIM3->SR & 0X0001)//溢出中断
//	{	
//	    //添加中断处理程序
////		t = !t;	   //取反标志位
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //一个位操作PB1口输出低电平点亮LED灯
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // 一个位操作 PB1口输出高电平关闭LED灯
//		
//		CLK2 = ~CLK2;
//	}				   
//	TIM3->SR &= ~(1<<0);//清除中断标志位
//	TIM_Cmd(TIM3, DISABLE);						 //关定时器3，在main函数内打开
}

void TIM4_IRQHandler(void)			   //定时器4全局中断服务函数
{
//	if(TIM4->SR & 0X0001)//溢出中断
//	{	
//	    //添加中断处理程序
//		t = !t;	   //取反标志位
//		if(t == 1)
//			
//			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //一个位操作PB1口输出低电平点亮LED灯
//		else
//	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // 一个位操作 PB1口输出高电平关闭LED灯			    				   				     	    	
//	}				   
//	TIM4->SR &= ~(1<<0);//清除中断标志位
}

void I2C1_EV_IRQHandler(void)		   //I2C1事件中断服务函数
{
}

void I2C1_ER_IRQHandler(void)		   //I2C1错误中断服务函数
{
}

void I2C2_EV_IRQHandler(void)		   //I2C2事件中断服务函数
{
}

void I2C2_ER_IRQHandler(void)		   //I2C2错误中断服务函数
{
}

void SPI1_IRQHandler(void)			   //SPI1全局中断服务函数
{
}

void SPI2_IRQHandler(void)			   //SPI2全局中断服务函数
{
}

//void USART1_IRQHandler(void)		   //串口1全局中断服务函数
//{
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断有效,若接收数据寄存器满
//  	{
//    	//buff_485[0] = USART_ReceiveData(USART1);	//接收数据
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(USART1);	//接收数据
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(USART1);	//接收数据
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(USART1);	//接收数据
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(USART1);	//接收数据
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(USART1);	//接收数据
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(USART1);	//接收数据
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(USART1);	//接收数据
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //如果接收完数据，接收状态归零
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //进行校验
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //如果校验正确 且地址也正确
//					{
//						//ming_ling_jie_shi();         //解释命令
//						if(buff_485[3] == 0x08 )	feng = 0;  //上 蜂鸣器发生
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //发送停止信号
//						{
//						 	feng = 1;	//关蜂鸣器
//						}
//					}
//					else  //否则不正确
//					{
//					 	for(t = 0;t<9;t++)           //清零
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(USART1);	//接收数据
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(USART1);	//接收数据
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //进行校验

//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //如果校验正确 且地址也正确
//				{
//					//ming_ling_jie_shi();         //解释命令
//				}
//				else  //否则不正确
//				{
//				 	for(t = 0;t<9;t++)           //清零
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}



//	if(USART_GetITStatus(USART1, USART_IT_TXE) == SET)      // 发送中断有效 ； 
//  	{   
//		//USART_ClearFlag(USART1, USART_FLAG_TC);                //清串口1发送标志
//
//		f ++;
//		if(f >= 2)	{f = 0; } // 清除USART1的发送中断 ； 
//		else  
//		{
//			USART_ClearITPendingBit(USART1, USART_IT_TXE);     // 清除USART1的发送中断 
//			USART_SendData(USART1, 0x97);
//		}
//  	}   
//}  	 

/*void USART2_IRQHandler(void)		   //串口1全局中断服务函数
{ 
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断有效,若接收数据寄存器满
     {
      Temp[counter] = USART_ReceiveData(USART2);   //接收数据
	  if(counter == 0 && Temp[0] != 0x55) return;      //第 0 号数据不是帧头，跳过
      counter++; 
      if(counter==11) //接收到 11 个数据
      { 
         memcpy(Re_buf,Temp,11);
         counter=0; //重新赋值，准备下一帧数据的接收
         sign=1;
      }    
   }




		
//		switch(counter)
//        {
//            case 0:
//				Re_buf[0] = USART_ReceiveData(USART2);	//接收数据
//                if(Re_buf[0] == 0x55)  counter = 1; 
//                else   counter = 0;   
//                break;
//            case 1:
//                Re_buf[1] = USART_ReceiveData(USART2);	//接收数据
//                counter = 2;
//                break;
//            case 2:
//                Re_buf[2] = USART_ReceiveData(USART2);	//接收数据
//                counter = 3;
//                break;
//            case 3:
//                Re_buf[3] = USART_ReceiveData(USART2);	//接收数据
//                counter = 4;
//                break;
//            case 4:
//                Re_buf[4] = USART_ReceiveData(USART2);	//接收数据
//                counter = 5;
//                break;
//            case 5:
//                Re_buf[5] = USART_ReceiveData(USART2);	//接收数据
//                counter = 6;
//                break;
//            case 6:
//                Re_buf[6] = USART_ReceiveData(USART2);	//接收数据
//                counter = 7;
//                break;
//            case 7:
//                Re_buf[7] = USART_ReceiveData(USART2);	//接收数据
//                counter = 8;
//                break;
//			case 8:
//                Re_buf[8] = USART_ReceiveData(USART2);	//接收数据
//                counter = 9;
//                break;
//			case 9:
//                Re_buf[9] = USART_ReceiveData(USART2);	//接收数据
//                counter = 10;
//                break;
//            case 10:
//                Re_buf[10] = USART_ReceiveData(USART2);	//接收数据
//                counter = 0;
//                he = 0;
//                for(t=0; t<10; t++)
//                    he += Re_buf[t];             //进行校验
//				//he = he%256;
//
//                if(Re_buf[10] == he && Re_buf[0] == 0x55)     //如果校验正确置位sign=1;
//				{
//					for(t=0; t<11; t++)	temp_buf[t]	= Re_buf[t];
//					sign = 1;        //解释命令
//				}
//
//                break;
//            default:  break;
//        }	 	
}*/



/*void USART3_IRQHandler(void)		   //串口3全局中断服务函数
{
   if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断有效,若接收数据寄存器满
     {
      Temp[counter] = USART_ReceiveData(USART3);   //接收数据
	  if(counter == 0 && Temp[0] != 0x55) return;      //第 0 号数据不是帧头，跳过
      counter++; 
      if(counter==11) //接收到 11 个数据
      { 
         memcpy(Re_buf,Temp,11);
         counter=0; //重新赋值，准备下一帧数据的接收
         sign=1;
      }
		 }
}		 */



//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断有效,若接收数据寄存器满
//  	{
//    	//buff_485[0] = USART_ReceiveData(USART3);	//接收数据
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(USART3);	//接收数据
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(USART3);	//接收数据
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(USART3);	//接收数据
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(USART3);	//接收数据
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(USART3);	//接收数据
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(USART3);	//接收数据
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(USART3);	//接收数据
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //如果接收完数据，接收状态归零
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //进行校验
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //如果校验正确 且地址也正确
//					{
//						//ming_ling_jie_shi();         //解释命令
//						if(buff_485[3] == 0x04 )	{feng = 0; LR_uart_buf = buff_485[4];CWW1 = 1;} //左 蜂鸣器发生。buff_485[4]是指令速度
//						if(buff_485[3] == 0x02 )	{feng = 0; LR_uart_buf = buff_485[4];CWW1 = 0;} //右 蜂鸣器发生。buff_485[4]是指令速度
//						if(buff_485[3] == 0x08 )	{feng = 0; UD_uart_buf = buff_485[5];CWW2 = 1;} //上 蜂鸣器发生。buff_485[5]是指令速度
//						if(buff_485[3] == 0x10 )	{feng = 0; UD_uart_buf = buff_485[5];CWW2 = 0;} //下 蜂鸣器发生。buff_485[5]是指令速度
//						if(buff_485[3] == 0x0C )    //左上
//						{
//							fang_xiang = 1;
//							CWW1 = 1;
//							CWW2 = 1;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						if(buff_485[3] == 0x14 )    //左下
//						{
//							fang_xiang = 2;
//							CWW1 = 1;
//							CWW2 = 0;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						if(buff_485[3] == 0x0A )    //右上
//						{
//							fang_xiang = 3;
//							CWW1 = 0;
//							CWW2 = 1;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						if(buff_485[3] == 0x12 )    //右下
//						{
//							fang_xiang = 4;
//							CWW1 = 0;
//							CWW2 = 0;
//							feng = 0;
//							LR_uart_buf = buff_485[4];
//							UD_uart_buf = buff_485[5];
//						}
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //发送停止信号
//						{
//						 	feng = 1;	//关蜂鸣器
//							LR_uart_buf = 0; //速度指令清零
//							UD_uart_buf = 0;
//							fang_xiang = 0;
//						}
//					}
//					else  //否则不正确
//					{
//					 	for(t = 0;t<9;t++)           //清零
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(USART3);	//接收数据
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(USART3);	//接收数据
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //进行校验
//
//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //如果校验正确 且地址也正确
//				{
//					//ming_ling_jie_shi();         //解释命令
//				}
//				else  //否则不正确
//				{
//				 	for(t = 0;t<9;t++)           //清零
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}

void EXTI15_10_IRQHandler(void)		   //外部中断10【15:10】中断服务函数
{
//	if(EXTI_GetITStatus(EXTI_Line10) != RESET) 
//	{
//     //添加中断处理程序
////		t = !t;	   //取反标志位
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //PB1口输出低电平点亮LED1
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // 一个位操作 关闭LED1
//
//		led_PB13 = ~led_PB13;	   //取反
//	
//		 EXTI_ClearFlag(EXTI_Line10);			          //清除中断标志（必须）
//	     EXTI_ClearITPendingBit(EXTI_Line10);			  //清除中断挂起位
//	 }
}

void RTCAlarm_IRQHandler(void)		   //联到EXTI的RTC闹钟中断服务函数
{
}

void USBWakeUp_IRQHandler(void)		   //联到EXTI的从USB待机唤醒中断服务函数
{
}

void TIM8_BRK_IRQHandler(void)		   //定时器8断开中断服务函数
{
}

void TIM8_UP_IRQHandler(void)		   //定时器8更新中断服务函数
{
}

void TIM8_TRG_COM_IRQHandler(void)	   //定时器8触发和通信中断服务函数
{
}

void TIM8_CC_IRQHandler(void)		   //定时器8捕获比较中断服务函数
{
}

void ADC3_IRQHandler(void)			   //ADC3全局中断服务函数
{
}

void FSMC_IRQHandler(void)			   //FSMC全局中断服务函数
{
}

void SDIO_IRQHandler(void)			   //SDIO全局中断服务函数
{
}

void TIM5_IRQHandler(void)			   //定时器5全局中断服务函数
{
//	if(TIM5->SR & 0X0001)//溢出中断
//	{	
//	    //添加中断处理程序
//		t = !t;	   //取反标志位
//		if(t == 1)
//			
//			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //一个位操作PB1口输出低电平点亮LED灯
//		else
//	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // 一个位操作 PB1口输出高电平关闭LED灯			    				   				     	    	
//	}				   
//	TIM5->SR &= ~(1<<0);//清除中断标志位
}

void SPI3_IRQHandler(void)			   //SPI3全局中断服务函数
{
}

void UART4_IRQHandler(void)			   //串口4全局中断服务函数
{
//	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断有效,若接收数据寄存器满
//  	{
//    	//buff_485[0] = USART_ReceiveData(UART4);	//接收数据
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(UART4);	//接收数据
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(UART4);	//接收数据
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(UART4);	//接收数据
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(UART4);	//接收数据
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(UART4);	//接收数据
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(UART4);	//接收数据
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(UART4);	//接收数据
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //如果接收完数据，接收状态归零
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //进行校验
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //如果校验正确 且地址也正确
//					{
//						//ming_ling_jie_shi();         //解释命令
//						if(buff_485[3] == 0x08 )	feng = 0;  //上 蜂鸣器发生
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //发送停止信号
//						{
//						 	feng = 1;	//关蜂鸣器
//						}
//					}
//					else  //否则不正确
//					{
//					 	for(t = 0;t<9;t++)           //清零
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(UART4);	//接收数据
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(UART4);	//接收数据
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //进行校验
//
//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //如果校验正确 且地址也正确
//				{
//					//ming_ling_jie_shi();         //解释命令
//				}
//				else  //否则不正确
//				{
//				 	for(t = 0;t<9;t++)           //清零
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}
}

void UART5_IRQHandler(void)			   //串口5全局中断服务函数
{
//	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断有效,若接收数据寄存器满
//  	{
//    	//buff_485[0] = USART_ReceiveData(UART5);	//接收数据
//		switch(uart_1)
//        {
//            case 0:
//				buff_485[0] = USART_ReceiveData(UART5);	//接收数据
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0xef) || (buff_485[0] == 0x68))
//				{
//                	uart_1 = 1;
//				} 
//                else
//                    uart_1 = 0;
//                break;
//            case 1:
//                buff_485[1] = USART_ReceiveData(UART5);	//接收数据
//                uart_1 ++;
//                break;
//            case 2:
//                buff_485[2] = USART_ReceiveData(UART5);	//接收数据
//                uart_1 ++;
//                break;
//            case 3:
//                buff_485[3] = USART_ReceiveData(UART5);	//接收数据
//                uart_1 ++;
//                break;
//            case 4:
//                buff_485[4] = USART_ReceiveData(UART5);	//接收数据
//                uart_1 ++;
//                break;
//            case 5:
//                buff_485[5] = USART_ReceiveData(UART5);	//接收数据
//                uart_1 ++;
//                break;
//            case 6:
//                buff_485[6] = USART_ReceiveData(UART5);	//接收数据
//                if((buff_485[0] == 0xff) || (buff_485[0] == 0x68))
//                {
//                    uart_1 = 0;         //如果接收完数据，接收状态归零
//                    he = 0;
//                    for(t=1; t<6; t++)
//                        he += buff_485[t];             //进行校验
//             
//                    if(buff_485[6] == he && buff_485[1] == di_zhi)     //如果校验正确 且地址也正确
//					{
//						//ming_ling_jie_shi();         //解释命令
//						if(buff_485[3] == 0x08 )	feng = 0;  //上 蜂鸣器发生
//						//else aa = 0;
//						if(buff_485[2] == 0 && buff_485[3] == 0 && buff_485[4] == 0 && buff_485[5] == 0)  //发送停止信号
//						{
//						 	feng = 1;	//关蜂鸣器
//						}
//					}
//					else  //否则不正确
//					{
//					 	for(t = 0;t<9;t++)           //清零
//							buff_485[t] = 0;	
//					}
//                } 
//				else if( buff_485[0] == 0xef )
//                    uart_1 ++;
//                break;
//            case 7:
//                buff_485[7] = USART_ReceiveData(UART5);	//接收数据
//                uart_1 ++;
//                break;
//            case 8:
//                buff_485[8] = USART_ReceiveData(UART5);	//接收数据
//                uart_1 = 0;
//                he = 0;
//                for(t=1; t<8; t++)
//                    he += buff_485[t];             //进行校验
//
//                if(buff_485[8] == he && buff_485[1] == di_zhi)     //如果校验正确 且地址也正确
//				{
//					//ming_ling_jie_shi();         //解释命令
//				}
//				else  //否则不正确
//				{
//				 	for(t = 0;t<9;t++)           //清零
//						buff_485[t] = 0;	
//				}
//                break;
//            default:  break;
//        }	 
//  	}
}

void TIM6_IRQHandler(void)			   //定时器6全局中断服务函数
{
//	if(TIM6->SR & 0X0001)//溢出中断
//	{	
//	    //添加中断处理程序
//		t = !t;	   //取反标志位
//		if(t == 1)
//			
//			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //一个位操作PB1口输出低电平点亮LED灯
//		else
//	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // 一个位操作 PB1口输出高电平关闭LED灯			    				   				     	    	
//	}				   
//	TIM6->SR &= ~(1<<0);//清除中断标志位
}

void TIM7_IRQHandler(void)			   //定时器7全局中断服务函数
{
//	if(TIM7->SR & 0X0001)//溢出中断
//	{	
//	    //添加中断处理程序
////		t = !t;	   //取反标志位
////		if(t == 1)
////			
////			GPIO_ResetBits(GPIOB , GPIO_Pin_1);		  //一个位操作PB1口输出低电平点亮LED灯
////		else
////	 		GPIO_SetBits(GPIOB, GPIO_Pin_1);	      // 一个位操作 PB1口输出高电平关闭LED灯
//
//		//GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1)))); /* LED1 取反 */	
//		
//		//led_PB13 = ~led_PB13;	   //取反
//		
//		//CLK1 = ~CLK1;
//		//CLK2 = ~CLK2;
//		sao_miao_xian_shi();               //2ms扫描一次数码管
//		
//		Led_T ++; //200msLED发光
//		
//	}				   
//	TIM7->SR &= ~(1<<0);//清除中断标志位
}

void DMA2_Channel1_IRQHandler(void)	   //DMA2通道1全局中断服务函数
{
}

void DMA2_Channel2_IRQHandler(void)	   //DMA2通道2全局中断服务函数
{
}

void DMA2_Channel3_IRQHandler(void)	   //DMA2通道3全局中断服务函数
{
}

void DMA2_Channel4_5_IRQHandler(void)  //DMA2通道4和DMA2通道5全局中断服务函数
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

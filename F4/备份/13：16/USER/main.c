#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "OV7670.h"
#include "dcmi.h" 

extern u8 pic[120][320];

int main(void)
{ 
	delay_init(168);		//延时初始化 
	uart_init(256000);	//串口初始化波特率为115200
	while(OV7670_init()!=0)
	{
		printf("OV7670_InitRetry\r\n");
		delay_ms(400);
	}
	printf("OV7670_InitOk\r\n");
	delay_ms(1800);
	
	My_DCMI_Init();
	DCMI_DMA_Init((u32)pic,9600,DMA_MemoryDataSize_Word);
	DCMI_Start();
	while(1)
	{
		;
	}
}


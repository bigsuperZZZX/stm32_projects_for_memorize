#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/

#define UART_RX_LEN 7  //DMA每次传输的数据量

void uart_init(u32 bound);
#endif



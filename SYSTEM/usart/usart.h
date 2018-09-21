#ifndef _USART_H
#define _USART_H
#include "sys.h"
#include "stdio.h"	


#define Usart1RxLen	256	
#define Usart1TxLen	256

extern u16 Usart1RxCnt;
extern u16 OldUsart1RxCnt;
extern u16 Usart1FrameLen;
extern u8 Usart1RxBuf[Usart1RxLen];
extern u8 Usart1TxBuf[Usart1TxLen];
extern u8 Usart1RecvEnd;
extern u8 Usart1Busy;
extern u16 Usart1SendLen;
extern u16 Usart1SendNum;
	  	

extern UART_HandleTypeDef UART1_Handler; //UART句柄


//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void Usart1ReciveFrameEnd(void);


#endif

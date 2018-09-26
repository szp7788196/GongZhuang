#ifndef _USART_H
#define _USART_H
#include "sys.h"
#include "stdio.h"	


#define Usart3RxLen	256	
#define Usart3TxLen	256

extern u16 Usart3RxCnt;
extern u16 OldUsart3RxCnt;
extern u16 Usart3FrameLen;
extern u8 Usart3RxBuf[Usart3RxLen];
extern u8 Usart3TxBuf[Usart3TxLen];
extern u8 Usart3RecvEnd;
extern u8 Usart3Busy;
extern u16 Usart3SendLen;
extern u16 Usart3SendNum;
	  	

extern UART_HandleTypeDef UART3_Handler; //UART句柄


//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void Usart3ReciveFrameEnd(void);


#endif

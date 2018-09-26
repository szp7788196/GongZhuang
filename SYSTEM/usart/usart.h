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
	  	

extern UART_HandleTypeDef UART3_Handler; //UART���


//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void Usart3ReciveFrameEnd(void);


#endif

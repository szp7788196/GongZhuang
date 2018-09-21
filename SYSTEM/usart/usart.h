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
	  	

extern UART_HandleTypeDef UART1_Handler; //UART���


//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void Usart1ReciveFrameEnd(void);


#endif

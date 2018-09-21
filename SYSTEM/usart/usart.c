#include "usart.h"
#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��os,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os ʹ��	  
#endif

u16 Usart1RxCnt = 0;
u16 OldUsart1RxCnt = 0;
u16 Usart1FrameLen = 0;
u8 Usart1RxBuf[Usart1RxLen];
u8 Usart1TxBuf[Usart1TxLen];
u8 Usart1RecvEnd = 0;
u8 Usart1Busy = 0;
u16 Usart1SendLen = 0;
u16 Usart1SendNum = 0;

#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif 



UART_HandleTypeDef UART1_Handler; //UART���

//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound)
{	
	//UART ��ʼ������
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //������
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()��ʹ��UART1
	
	//HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������(ʹ�ûص����������ж���Ҫ���øú�����
  
}

//UART�ײ��ʼ����ʱ��ʹ�ܣ��������ã��ж�����
//�˺����ᱻHAL_UART_Init()����
//huart:���ھ��

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO�˿�����
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//����Ǵ���1�����д���1 MSP��ʼ��
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
		__HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//����
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//����ΪUSART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA10
		__HAL_UART_DISABLE_IT(huart,UART_IT_TC);
		__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);		//���������ж�
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//ʹ��USART1�ж�ͨ��
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
	
	}
}

void Usart1ReciveFrameEnd(void)
{
	if(Usart1RxCnt)
	{
		if(OldUsart1RxCnt == Usart1RxCnt)
		{
			Usart1FrameLen = Usart1RxCnt;
			OldUsart1RxCnt = 0;
			Usart1RxCnt = 0;
			Usart1RecvEnd = 0xAA;
		}
		else
		{
			OldUsart1RxCnt = Usart1RxCnt;
		}
	}
}

//����1�жϷ������
void USART1_IRQHandler(void)                	
{ 
	u8 rxdata;

	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
        HAL_UART_Receive(&UART1_Handler,&rxdata,1,1000); 
		
		if(Usart1RxCnt<Usart1RxLen && Usart1Busy == 0)
		{
			Usart1RxBuf[Usart1RxCnt]=rxdata;
			Usart1RxCnt++;
		}
		
		__HAL_UART_CLEAR_FLAG(&UART1_Handler,UART_FLAG_RXNE);
	}
	
	else if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_CTS)!=RESET))
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler, UART_FLAG_CTS);
	}
	else if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_LBD)!=RESET))
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler, UART_FLAG_LBD);
	}
	else if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TXE)!=RESET))
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler, UART_FLAG_TXE);
	}
	else if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=RESET))
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler, UART_FLAG_TC);
	}
	else if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_IDLE)!=RESET))
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler, UART_FLAG_IDLE);
	}
	else if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_ORE)!=RESET))
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler, UART_FLAG_ORE);
	}
	else if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_NE)!=RESET))
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler, UART_FLAG_NE);
	}
	else if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_FE)!=RESET))
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler, UART_FLAG_FE);
	}
	else if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_PE)!=RESET))
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler, UART_FLAG_PE);
	}
	else
	{
		__HAL_UART_CLEAR_FLAG(&UART1_Handler, ((uint32_t)0x004FFFFF));
	}
	HAL_UART_IRQHandler(&UART1_Handler);	

} 




#include "usart.h"
#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用os,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os 使用	  
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
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif 



UART_HandleTypeDef UART1_Handler; //UART句柄

//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound)
{	
	//UART 初始化设置
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //波特率
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()会使能UART1
	
	//HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量(使用回调函数处理中断需要调用该函数）
  
}

//UART底层初始化，时钟使能，引脚配置，中断配置
//此函数会被HAL_UART_Init()调用
//huart:串口句柄

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	//复用为USART1
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		__HAL_UART_DISABLE_IT(huart,UART_IT_TC);
		__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);		//开启接收中断
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//抢占优先级3，子优先级3
	
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

//串口1中断服务程序
void USART1_IRQHandler(void)                	
{ 
	u8 rxdata;

	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
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




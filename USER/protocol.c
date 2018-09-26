#include "protocol.h"
#include "common.h"
#include "delay.h"
#include "usart.h"
#include "string.h"
#include "cd4051.h"


u8 GetDeviceUUID(u8 *uuid)
{
	u8 ret = 0;
	u8 i = 0;
	u8 re_try_cnt = 0;
	
	u8 send_buf1[14]="AT+PWRCTL=0\r\n\0";
	u8 send_buf2[10]="AT+UUID\r\n\0";
	
	RE_SEND1:
	HAL_UART_Transmit(&UART3_Handler, send_buf1, 13,1000);
	
	i = 10;
	
	while(-- i)
	{
		delay_ms(300);
		
		if(Usart3RecvEnd == 0xAA)
		{
			Usart3RecvEnd = 0;
			
			if(MyStrstr(Usart3RxBuf, (u8 *)"OK", Usart3FrameLen, 2) != 0xFFFF)
			{
				memset(Usart3RxBuf,0,Usart3FrameLen);
				i = 1;
				ret = 1;
			}
		}
		
		if(ret == 0)
		{
			re_try_cnt ++;
			
			if(re_try_cnt < 10)
			{
				goto RE_SEND1;
			}
			else
			{
				return 0;
			}
		}
	}
	
	RE_SEND2:
	HAL_UART_Transmit(&UART3_Handler, send_buf2, 9,1000);
	
	i = 10;
	
	while(-- i)
	{
		delay_ms(300);
		
		if(Usart3RecvEnd == 0xAA)
		{
			Usart3RecvEnd = 0;
			
			if(MyStrstr(Usart3RxBuf, (u8 *)"OK", Usart3FrameLen, 2) != 0xFFFF)
			{
				get_str1(Usart3RxBuf, (u8 *)"uuid: ", 1, (u8 *)"\r\n\r\nOK", 1, uuid);
				
				memset(Usart3RxBuf,0,Usart3FrameLen);
				i = 1;
				ret = strlen((char *)uuid);
			}
		}
		
		if(ret == 0)
		{
			re_try_cnt ++;
			
			if(re_try_cnt < 10)
			{
				goto RE_SEND2;
			}
			else
			{
				return 0;
			}
		}
	}
	
	return ret;
}



































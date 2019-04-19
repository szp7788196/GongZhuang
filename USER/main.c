#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
#include "timer.h"
#include "protocol.h"
#include "common.h"
#include "cd4051.h"
#include "at_protocol.h"

int main(void)
{
	u8 i = 0;
	u8 ret = 0;
	
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(9600);              	//��ʼ��USART
    LED_Init();                     //��ʼ��LED 
    KEY_Init();                     //��ʼ������
	TIM3_Init(1000,9000);			//��ʼ����ʱ��
    SDRAM_Init();                   //SDRAM��ʼ��
    LCD_Init();                     //LCD��ʼ��
	CD4051_Init();
	
	POINT_COLOR=RED; 

	LCD_Clear(BLACK);
	BACK_COLOR = BLACK;
	POINT_COLOR = GREEN;
	
	ResetUUIDGroup();
	AT_CommandInit();
	ShowSerialNumber();
	
	POINT_COLOR = WHITE;
	
    while(1)
    {
		for(i = 0; i < 10; i ++)
		{
			CD4051SetChannel(9 - i);
			
			memset(UUID,0,18);
		
			ret = GetDeviceUUID(UUID);
			
			if(ret == 17)
			{
				LCD_ShowString(10 + 48,80 + (40 * i),576,32,32,UUID); 
				
				memcpy(UUIDGroup[i],UUID,17);
			}
			else
			{
				LCD_ShowString(10 + 48,80 + (40 * i),576,32,32,StrNull);
				memcpy(UUIDGroup[i],StrNull,17);
			}
		}
	}
}


























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

int main(void)
{
	u8 i = 0;
	u8 ret = 0;
	
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
    delay_init(180);                //初始化延时函数
    uart_init(9600);              	//初始化USART
    LED_Init();                     //初始化LED 
    KEY_Init();                     //初始化按键
	TIM3_Init(100,9000);			//初始化定时器
    SDRAM_Init();                   //SDRAM初始化
    LCD_Init();                     //LCD初始化
	
	POINT_COLOR=RED; 

	LCD_Clear(BLACK);
	BACK_COLOR = BLACK;
	POINT_COLOR = GREEN;
	
	ShowSerialNumber();
	
	POINT_COLOR = WHITE;
	
    while(1)
    {
		for(i = 0; i < 10; i ++)
		{
			CD4051SetChannel(i);
			
			memset(UUID,0,37);
		
			ret = GetDeviceUUID(UUID);
			
			if(ret == 36)
			{
				LCD_ShowString(10 + 48,80 + (40 * i),576,32,32,UUID); 
			}
			else
			{
				LCD_ShowString(10 + 48,80 + (40 * i),576,32,32,StrNull); 
			}
		}
	}
}


























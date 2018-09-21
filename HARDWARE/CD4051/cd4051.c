#include "cd4051.h"



void CD4051_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOB时钟
	
    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
	CD4051_BIT0 = 1;
	CD4051_BIT1 = 1;
	CD4051_BIT2 = 1;
	CD4051_BIT3 = 1;
	CD4051_BIT4 = 1;
	CD4051_BIT5 = 1;
}


void CD4051SetChannel(u8 ch)
{
	switch(ch)
	{
		case 0:					//1-1
			CD4051_BIT0 = 0;
			CD4051_BIT1 = 0;
			CD4051_BIT2 = 1;
			CD4051_BIT3 = 1;
			CD4051_BIT4 = 1;
			CD4051_BIT5 = 1;
		break;
		
		case 1:					//1-3
			CD4051_BIT0 = 0;
			CD4051_BIT1 = 1;
			CD4051_BIT2 = 1;
			CD4051_BIT3 = 1;
			CD4051_BIT4 = 1;
			CD4051_BIT5 = 1;
		break;
		
		case 2:					//1-5
			CD4051_BIT0 = 1;
			CD4051_BIT1 = 0;
			CD4051_BIT2 = 1;
			CD4051_BIT3 = 1;
			CD4051_BIT4 = 1;
			CD4051_BIT5 = 1;
		break;
		
		case 3:					//2-0
			CD4051_BIT0 = 1;
			CD4051_BIT1 = 1;
			CD4051_BIT2 = 1;
			CD4051_BIT3 = 0;
			CD4051_BIT4 = 0;
			CD4051_BIT5 = 0;
		break;
		
		case 4:					//2-1
			CD4051_BIT0 = 1;
			CD4051_BIT1 = 1;
			CD4051_BIT2 = 1;
			CD4051_BIT3 = 0;
			CD4051_BIT4 = 0;
			CD4051_BIT5 = 1;
		break;
		
		case 5:					//2-2
			CD4051_BIT0 = 1;
			CD4051_BIT1 = 1;
			CD4051_BIT2 = 1;
			CD4051_BIT3 = 0;
			CD4051_BIT4 = 1;
			CD4051_BIT5 = 0;
		break;
		
		case 6:					//2-3
			CD4051_BIT0 = 1;
			CD4051_BIT1 = 1;
			CD4051_BIT2 = 1;
			CD4051_BIT3 = 0;
			CD4051_BIT4 = 1;
			CD4051_BIT5 = 1;
		break;
		
		case 7:					//2-4
			CD4051_BIT0 = 1;
			CD4051_BIT1 = 1;
			CD4051_BIT2 = 1;
			CD4051_BIT3 = 1;
			CD4051_BIT4 = 0;
			CD4051_BIT5 = 0;
		break;
		
		case 8:					//2-5
			CD4051_BIT0 = 1;
			CD4051_BIT1 = 1;
			CD4051_BIT2 = 1;
			CD4051_BIT3 = 1;
			CD4051_BIT4 = 0;
			CD4051_BIT5 = 1;
		break;
		
		case 9:					//2-6
			CD4051_BIT0 = 1;
			CD4051_BIT1 = 1;
			CD4051_BIT2 = 1;
			CD4051_BIT3 = 1;
			CD4051_BIT4 = 1;
			CD4051_BIT5 = 0;
		break;
		
		default:
			
		break;
	}
}




































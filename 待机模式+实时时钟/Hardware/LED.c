#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
}

void LED1_ON(void)						//led灯开启
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

void LED1_OFF(void)						//led灯关闭
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void LED1_Turn(void)					//led灯翻转当前的状态
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == 0)//读取A1口输出的值，判断是否为0（灯亮为0），为低电平
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);				//翻转为高电平，即灯灭
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2) == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
}

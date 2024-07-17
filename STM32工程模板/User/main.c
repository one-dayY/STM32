#include "stm32f10x.h"                  // Device header

int main(void)
{
	//配置时钟使能，库函数中这个函数来开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//第一个选择外设，第二个选择新的状态
	
	//配置结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//配置端口模式
	GPIO_Init(GPIOC,&GPIO_InitStructure);//第一个选择哪个GPIO，第二个选择参数的结构体
	
	//设置端口的高低电平进行点灯
//	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	while(1)
	{
		
	}
}

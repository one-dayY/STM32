#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	//电机方向控制脚初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_5;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	PWM_Init();
}

 void Motor_SetSpeed(int8_t Speed)
 {
	 //正转
	 if(Speed >= 0)
	 {
		 //设置方向
		 GPIO_SetBits(GPIOA,GPIO_Pin_7);					//PA7被驱动成高电平状态
		 GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		 //设置速度
		 PWM_Setcompare3(Speed);
	 }
	 //反转
	 else
	 {
		 GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		 GPIO_SetBits(GPIOA,GPIO_Pin_5);
		 PWM_Setcompare3(-Speed);
	 }
 }

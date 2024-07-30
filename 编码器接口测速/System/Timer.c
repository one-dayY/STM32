#include "stm32f10x.h"                  // Device header
#include "Encoder.h"

extern uint16_t Speed;

void Timer_Init(void)
{
	//开启RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//选择时基单元的时钟
	TIM_InternalClockConfig(TIM2);
	
	//配置时基单元
	//定义结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	//引出结构体成员
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			//选择1分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;					//1s
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	//使能更新中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	//配置NVIC
	//优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//定义结构体
	NVIC_InitTypeDef NVIC_InitStructure;
	//引出结构体成员
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//启动定时器
	TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		Speed = Encoder_Get();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

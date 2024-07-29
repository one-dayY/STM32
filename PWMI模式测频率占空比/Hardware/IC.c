#include "stm32f10x.h"                  // Device header

void IC_Init(void)
{
	//开启TIM3时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//开启GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//配置GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//选择时基单元的时钟
	TIM_InternalClockConfig(TIM3);
	
	//时基单元初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;				//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;				//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	//初始化输入捕获单元
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							//选择输入捕获的滤波器
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//极性选择
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;			//分频器选择
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//选择触发信号从哪个引脚输入
	TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);
	
	
	//配置TRGI的触发源为TI1FP1
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	//配置从模式位Reset
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	//启动定时器
	TIM_Cmd(TIM3,ENABLE);
}

uint32_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM3) + 1);				//fc = 1MHz = 10000000
}

uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1);
}

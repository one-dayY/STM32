#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	//开启RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);			//开启ADC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//开启GPIO时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//GPIO初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//用结构体初始化ADC
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	//开启ADC电源
	ADC_Cmd(ADC1,ENABLE);
	
	//对ADC进行校准
	ADC_ResetCalibration(ADC1);				//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);	//获取复位校准状态，清0跳出
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(uint8_t ADC_Channel)		//只需要指定一个转换的通道，返回值就是指定通道的结果
{
	//选择规则组的输入通道
	ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);	
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);				//软件触发AD转换
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//等待EOC标志位，即等待AD转换结果，1跳出
	return ADC_GetConversionValue(ADC1);
}

#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"

int main(void)
{
	Buzzer_Init();
	LightSensor_Init();

	while(1)
	{
		if(LightSensor_Get() == 1)		//判断返回的状态，当输入为高电平，即遮住光敏电阻
		{
			Buzzer_ON();				//蜂鸣器发出声响
		}
		else
		{
			Buzzer_OFF();
		}
	}
}

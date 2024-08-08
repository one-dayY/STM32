#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"

int main(void)
{
	OLED_Init();
	MyRTC_Init();
	
	//开启PWR时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	
	OLED_ShowString(1,1,"CNT:");			//显示秒计数器
	OLED_ShowString(2,1,"ALR:");			//显示闹钟值
	OLED_ShowString(3,1,"ALRF:");			//闹钟标志位
	
	//WKUP引脚唤醒功能
	PWR_WakeUpPinCmd(ENABLE);
	
	//设定闹钟
	uint32_t Alarm;
	Alarm = RTC_GetCounter() + 10;
	RTC_SetAlarm(Alarm);
	OLED_ShowNum(2,6,Alarm,10);
	
	while(1)
	{
		OLED_ShowNum(1,6,RTC_GetCounter(),10);		//显示32位的秒计数器
		OLED_ShowNum(3,6,RTC_GetFlagStatus(RTC_FLAG_ALR),1);
		
		OLED_ShowString(4,1,"Running");
		Delay_ms(100);
		OLED_ShowString(4,1,"       ");
		Delay_ms(100);
		
		OLED_ShowString(4,9,"STANDBY");
		Delay_ms(1000);
		OLED_ShowString(4,9,"       ");
		Delay_ms(100);
		
		OLED_Clear();
		
		//进入待机模式
		PWR_EnterSTANDBYMode();
	}
}

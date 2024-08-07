#include "stm32f10x.h"                  // Device header
#include <time.h>

uint16_t MyRTC_Time[] = {2024,8,7,11,56,43};

void MyRTC_SetTime(void)
{
	time_t time_cnt;
	struct tm time_date;
	
	time_date.tm_year = MyRTC_Time[0] - 1900;
	time_date.tm_mon = MyRTC_Time[1] - 1;
	time_date.tm_mday = MyRTC_Time[2];
	time_date.tm_hour = MyRTC_Time[3];
	time_date.tm_min = MyRTC_Time[4];
	time_date.tm_sec = MyRTC_Time[5];
	
	time_cnt = mktime(&time_date) - 8 * 60 * 60;		//北京时间
	
	RTC_SetCounter(time_cnt);
	RTC_WaitForLastTask();
}

void MyRTC_ReadTime(void)
{
	time_t time_cnt;
	struct tm time_date;
	
	time_cnt = RTC_GetCounter() + 8 * 60 * 60;
	time_date = *localtime(&time_cnt);
	
	MyRTC_Time[0] = time_date.tm_year + 1900;
	MyRTC_Time[1] = time_date.tm_mon + 1;
	MyRTC_Time[2] = time_date.tm_mday;
	MyRTC_Time[3] = time_date.tm_hour;
	MyRTC_Time[4] = time_date.tm_min;
	MyRTC_Time[5] = time_date.tm_sec;
}

void MyRTC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);			//开启PER时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);			//开启BKP时钟
	
	PWR_BackupAccessCmd(ENABLE);								//使能PWR
	
	if(BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		RCC_LSEConfig(RCC_LSE_ON);									//开启LSE时钟
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET);			//等待LSE时钟启动完成
		
		//选择RTCCLK时钟源
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);					//使能时钟
		
		RTC_WaitForSynchro();					//等待同步
		RTC_WaitForLastTask();					//等待上一次操作完成
		
		//配置预分频器
		RTC_SetPrescaler(32768 - 1);			//会自动调用进入和退出配置模式的代码
		RTC_WaitForLastTask();
		
		//设置时间
		MyRTC_SetTime();
		BKP_WriteBackupRegister(BKP_DR1,0xA5A5);
	}
	else
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
}

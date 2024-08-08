#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

int main(void)
{
	OLED_Init();
	Key_Init();

	OLED_ShowString(1,1,"IWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		OLED_ShowString(2,1,"IWDGRST");
		Delay_ms(500);
		OLED_ShowString(2,1,"       ");
		Delay_ms(100);
		
		RCC_ClearFlag();
	}
	else
	{
		OLED_ShowString(3,1,"RST");
		Delay_ms(500);
		OLED_ShowString(3,1,"   ");
		Delay_ms(100);
	}
	
	//解除写保护
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);			
	//配置预分频和重装值
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2499);									//1000ms
	//喂狗
	IWDG_ReloadCounter();
	//启动看门狗
	IWDG_Enable();
	
	while(1)
	{
		Key_GetNum();		//按住按键不放，主循环就会阻塞，不能及时喂狗，独立看门狗就会复位
		
		IWDG_ReloadCounter();
		
		OLED_ShowString(4,1,"FEED");
		Delay_ms(200);
		OLED_ShowString(4,1,"    ");
		Delay_ms(600);
	}
}

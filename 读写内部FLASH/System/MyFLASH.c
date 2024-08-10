#include "stm32f10x.h"                  // Device header

uint32_t MyFLASH_ReadWord(uint32_t Address)
{
	return *((__IO uint32_t*)(Address));
}

uint16_t MyFLASH_ReadHalfWord(uint32_t Address)
{
	return *((__IO uint16_t*)(Address));
}

uint8_t MyFLASH_ReadByte(uint32_t Address)
{
	return *((__IO uint8_t*)(Address));
}

void MyFLASH_EraseAllPages(void)
{
	FLASH_Unlock();						//对FLASH进行解锁
	FLASH_EraseAllPages();				//执行全擦除
	FLASH_Lock();						//对FLASH进行加锁
}

void MyFLASH_ErasePage(uint32_t Page_Address)
{
	FLASH_Unlock();
	FLASH_ErasePage(Page_Address);
	FLASH_Lock();	
}

void MyFlash_ProgramWord(uint32_t Address,uint32_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramWord(Address,Data);
	FLASH_Lock();
}

void MyFlash_ProgramHalfWord(uint32_t Address,uint16_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramHalfWord(Address,Data);
	FLASH_Lock();
}

#ifndef __MYFLASH_H__
#define __MYFALSH_H__

uint32_t MyFLASH_ReadWord(uint32_t Address);
uint32_t MyFLASH_ReadHalfWord(uint32_t Address);
uint32_t MyFLASH_ReadByte(uint32_t Address);

void MyFLASH_EraseAllPages(void);
void MyFLASH_ErasePage(uint32_t Page_Address);

void MyFlash_ProgramWord(uint32_t Address,uint32_t Data);
void MyFlash_ProgramHalfWord(uint32_t Address,uint32_t Data);

#endif

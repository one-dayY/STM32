#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_Size;

void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size)
{
	MyDMA_Size = Size;
	
	//开启DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	//初始化DMA
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	DMA_InitStructure.DMA_BufferSize = Size;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	//这里先不给使能，初始化后不会立刻工作，等后续调用Transfer后，再开始
	DMA_Cmd(DMA1_Channel1,DISABLE);
}

void DMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);						//失能
	DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_Size);	//给传输计数器赋值
	DMA_Cmd(DMA1_Channel1,ENABLE);						//使能
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);				//等待转运完成
	DMA_ClearFlag(DMA1_FLAG_TC1);							//清除标志位
}

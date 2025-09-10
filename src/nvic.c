#include <stm32f10x.h>
#include <nvic.h>

void nvic_init(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}


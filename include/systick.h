#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include <stm32f10x.h>

void systick_init();
void delay(volatile uint32_t);
void TimingDelay_Decrement(void);
//void SysTick_Handler(void);

#endif


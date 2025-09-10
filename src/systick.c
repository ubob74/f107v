#include <systick.h>
#include <stm32f10x.h>

static volatile uint32_t TimingDelay;

void delay(volatile uint32_t n_time);

void systick_init(void)
{
	SysTick_Config(SystemCoreClock / 1000);
}

void delay(volatile uint32_t nTime)
{
	TimingDelay = nTime * 100;
	while (TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
		TimingDelay--;
}


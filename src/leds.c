#include "leds.h"

void led_init(LED_TypeDef LED)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	if ((LED == USER_LED) | (LED == BOTH_LEDS)) {
		RCC_APB2PeriphClockCmd(USER_LED_GPIO_CLK, ENABLE);
		GPIO_InitStructure.GPIO_Pin = USER_LED_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(USER_LED_GPIO_PORT, &GPIO_InitStructure);
	}

	if ((LED == FAULT_LED) | (LED == BOTH_LEDS)) {
		RCC_APB2PeriphClockCmd(FAULT_LED_GPIO_CLK, ENABLE);
 
		GPIO_InitStructure.GPIO_Pin = FAULT_LED_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
		GPIO_Init(FAULT_LED_GPIO_PORT, &GPIO_InitStructure);
	}
}

void led_deinit(LED_TypeDef LED)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	if ((LED == USER_LED) | (LED == BOTH_LEDS)) {
		RCC_APB2PeriphClockCmd(USER_LED_GPIO_CLK, DISABLE);
		GPIO_InitStructure.GPIO_Pin = USER_LED_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(USER_LED_GPIO_PORT, &GPIO_InitStructure);
	}

	if ((LED == FAULT_LED) | (LED == BOTH_LEDS)) {
		RCC_APB2PeriphClockCmd(FAULT_LED_GPIO_CLK, DISABLE);
		GPIO_InitStructure.GPIO_Pin = FAULT_LED_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(FAULT_LED_GPIO_PORT, &GPIO_InitStructure);
	}  
}

void led_on(LED_TypeDef LED)
{
	if ((LED == USER_LED) | (LED == BOTH_LEDS)) {
		GPIO_SetBits(USER_LED_GPIO_PORT, USER_LED_PIN);
	}

	if ((LED == FAULT_LED) | (LED == BOTH_LEDS)) {
		GPIO_ResetBits(FAULT_LED_GPIO_PORT, FAULT_LED_PIN);
	}
}

void led_off(LED_TypeDef LED)
{
	if ((LED == USER_LED) | (LED == BOTH_LEDS)) {
		GPIO_ResetBits(USER_LED_GPIO_PORT, USER_LED_PIN);
	}

	if ((LED == FAULT_LED) | (LED == BOTH_LEDS)) {
		GPIO_SetBits(FAULT_LED_GPIO_PORT, FAULT_LED_PIN);
	}
}


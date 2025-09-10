#ifndef _LEDS_H_
#define _LEDS_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define USER_LED_PIN                 GPIO_Pin_10                 // PB.10 
#define USER_LED_GPIO_PORT           GPIOB                       // GPIOB 
#define USER_LED_GPIO_CLK            RCC_APB2Periph_GPIOB       

#define FAULT_LED_PIN                GPIO_Pin_12                 // PD.12 
#define FAULT_LED_GPIO_PORT          GPIOD                       // GPIOD 
#define FAULT_LED_GPIO_CLK           RCC_APB2Periph_GPIOD   

typedef enum
{
	FAULT_LED,
	USER_LED,
	BOTH_LEDS 
} LED_TypeDef;

void led_on(LED_TypeDef LED);
void led_off(LED_TypeDef LED);
void led_init(LED_TypeDef LED);
void led_deinit(LED_TypeDef LED);

#endif


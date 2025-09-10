#include <stm32f10x.h>
#include <uart.h>
#include <ringbuf.h>

int uart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStruct;

	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	/* GPIOD Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	/* AFIO clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/* Remap and enable USART2 */
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* USART2 TX pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* USART2 RX pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* USART2 Tx and Rx interrupts disable */
	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);

	USART_Init(USART2, &USART_InitStruct);
	USART_Cmd(USART2, ENABLE);

	return 0;
}

int uart_putchar(unsigned char ch)
{
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	USART_SendData(USART2, ch);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	return ch;
}

void do_uart(void)
{
	unsigned char c;

	while (rb_pull(&c, sizeof(c)) == sizeof(c))
		uart_putchar(c);
}


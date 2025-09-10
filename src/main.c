#include <stm32f10x.h>
#include <leds.h>
#include <stdlib.h>
#include <nvic.h>
#include <uart.h>
#include <ringbuf.h>
#include <i2c.h>
#include <hd44780.h>
#include <systick.h>

const char *data[] = { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };

static inline void init(void)
{
	rb_init();
	nvic_init();
	uart_init();
	led_init(USER_LED);
	i2c_init();
	systick_init();
	hd44780_init();
}

int main(void)
{
	int i = 0;
	const char *tmp;
	uint32_t sysclk = SystemCoreClock / 1000;

	init();

	led_on(USER_LED);

	printf("System Core Clock: %d\r\n", sysclk);

	hd44780_test();

	while (1) {
		do_uart();
		delay(2);
		tmp = data[i++ % 10];
		hd44780_update(tmp, strlen(tmp));
	}

	return 0;
}


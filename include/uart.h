#ifndef _CONSOLE_H_
#define _CONSOLE_H_

int uart_init(void);
int uart_putchar(unsigned char);
void do_uart(void);

#endif

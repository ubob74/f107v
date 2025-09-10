#include <stm32f10x.h>
#include <main.h>

void __attribute__ ((section(".loader"))) loader(void)
{
	main();
}


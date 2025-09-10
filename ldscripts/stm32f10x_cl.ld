ENTRY(Reset_Handler)

MEMORY
{
	ISR(rx)    : ORIGIN = 0x08000000, LENGTH = 4K
	LOADER(rx) : ORIGIN = 0x08001000, LENGTH = 4K
	FLASH (rx) : ORIGIN = 0x08002000, LENGTH = 250K
	RAM  (xrw) : ORIGIN = 0x20000000, LENGTH = 64K
}

/* stack */
_estack = 0x20002000;

SECTIONS
{
	.isr_vector :
	{
		. = ALIGN(4);

		_start_isr = .;

		KEEP(*(.isr_vector))    /* Startup code */
	} >ISR

	.loader :
	{
		. =  ALIGN(4);
		KEEP(*(.loader))
	} >LOADER

	.text :
	{
		/*. = ALIGN(4);
 
		__start_main = ABSOLUTE (.);*/

		*(.text .text.*)

		/*KEEP (*(.init))
		KEEP (*(.fini))*/

        . = ALIGN(4);
        /*_etext = .;
        _sidata = _etext;*/
	} >FLASH

	_sidata = ABSOLUTE (.);

	.data  : AT ( _sidata )
	{
		. = ALIGN(4);
		_sdata = . ;
		_data = . ;

        *(.data)
        *(.data.*)
        *(.rodata)
        *(.rodata.*)

        . = ALIGN(4);
        _edata = . ;
    } >RAM

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        _bss = .;

        *(.bss)
        *(.bss.*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = . ;
    } >RAM

    PROVIDE ( end = _ebss );
    PROVIDE ( _end = _ebss );
}


SRCS = loader.c main.c \
		core_cm3.c \
		stm32f10x_it.c \
		system_stm32f10x.c \
		misc.c \
		stm32f10x_bkp.c \
		stm32f10x_cec.c \
		stm32f10x_dac.c \
		stm32f10x_dma.c \
		stm32f10x_flash.c \
		stm32f10x_gpio.c \
		stm32f10x_iwdg.c \
		stm32f10x_rcc.c \
		stm32f10x_sdio.c \
		stm32f10x_tim.c \
		stm32f10x_wwdg.c \
		stm32f10x_adc.c \
		stm32f10x_can.c  \
		stm32f10x_crc.c  \
		stm32f10x_dbgmcu.c  \
		stm32f10x_exti.c  \
		stm32f10x_fsmc.c   \
		stm32f10x_i2c.c   \
		stm32f10x_pwr.c   \
		stm32f10x_rtc.c  \
		stm32f10x_spi.c   \
		stm32f10x_usart.c

STDLIB_SRCS = stdlib.c math.c

SRCS += leds.c uart.c nvic.c ringbuf.c i2c.c hd44780.c systick.c
SRCS += $(STDLIB_SRCS)

PROJ_NAME=main

# Location of the linker scripts
LDSCRIPT_INC=./ldscripts

###################################################

ARM_PREFIX=$(ARM_CROSS_COMPILE)
#arm-none-eabi-
CC=$(ARM_PREFIX)gcc
LD=$(ARM_PREFIX)ld
OBJCOPY=$(ARM_PREFIX)objcopy
OBJDUMP=$(ARM_PREFIX)objdump
SIZE=$(ARM_PREFIX)size

CFLAGS  = -Wall -g -std=gnu99 #-Os 
CFLAGS += -mlittle-endian
CFLAGS += -mthumb
CFLAGS += -mcpu=cortex-m3
CFLAGS += -nostdlib
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -ffreestanding
CFLAGS += -Wl,-Map=$(PROJ_NAME).map
CFLAGS += -DSTM32F10X_CL
CFLAGS += -DUSE_STDPERIPH_DRIVER

###################################################

vpath %.c src src/Libraries/CMSIS/CM3 \
		src/Libraries/STM32F10x_StdPeriph_Driver/src \
		src/Libraries/CMSIS/CM3/startup/gcc \
		src/stdlib

ROOT=$(shell pwd)

CFLAGS += -I./src -I./src/Libraries/CMSIS/CM3
CFLAGS += -I./src/Libraries/STM32F10x_StdPeriph_Driver/inc
CFLAGS += -I./include -I./include/stdlib

ASMS += src/Libraries/CMSIS/CM3/startup/gcc/startup_stm32f10x_cl.s

OBJS += $(SRCS:.c=.o)
OBJS += $(ASMS:.s=.o)

###################################################

.PHONY: lib proj

all: proj

proj: $(PROJ_NAME).elf

%.o: %.c
	${CC} -Wall -Os -g -fno-pic ${CFLAGS} -c -o $@ $^

%.o: %.s
	${CC} -Wall -g -fno-pic ${CFLAGS} -c -o $@ $^

built-in.o: ${OBJS}
	${LD} -r -o $@ $^

$(PROJ_NAME).elf: built-in.o
	$(LD) -T $(LDSCRIPT_INC)/stm32f10x_cl.ld --no-dynamic-linker -Map $(PROJ_NAME).map $^ -o $@
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -j .isr_vector -j .loader -j .text -j .data -j .rodata -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	$(OBJDUMP) -St $(PROJ_NAME).elf >$(PROJ_NAME).lst
	$(SIZE) $(PROJ_NAME).elf

clean:
	find ./ -name '*~' | xargs rm -f	
	find ./ -name '*.o' | xargs rm -f
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).map
	rm -f $(PROJ_NAME).lst


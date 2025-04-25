OUT = UART_INT
CFLAGS = -T stm32f051r8.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m0 -mthumb-interwork
CFLAGS += -mfloat-abi=soft -mfpu=fpv4-sp-d16
CFLAGS += -nostdlib
CFLAGS += -I.
CFLAGS += -Iinc

SRC = stm32f051r8_startup.c
SRC += ./src/main.c
SRC += ./src/rcc.c
SRC += ./src/gpio.c
SRC += ./src/uart.c

$(OUT):
	arm-none-eabi-gcc -g -o $(OUT).elf $(CFLAGS) $(SRC)
	arm-none-eabi-objcopy -O binary $(OUT).elf $(OUT).bin
	
.PHONY:  clean flash info
clean:
	rm $(OUT).elf $(OUT).bin
flash: 
	st-flash --reset write $(OUT).bin 0x8000000
info:
	st-info --probe
gdb_server:
	st-util

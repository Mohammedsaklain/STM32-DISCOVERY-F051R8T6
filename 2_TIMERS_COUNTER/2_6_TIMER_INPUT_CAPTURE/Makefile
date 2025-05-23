OUT = INPUT_CAPTURE
CFLAGS = -T stm32f051r8.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m0 -mthumb-interwork
CFLAGS += -mfloat-abi=soft -mfpu=fpv4-sp-d16
CFLAGS += -nostdlib
CFLAGS += -I.
CFLAGS += -Iinc

SRC = stm32f051r8_startup.c
SRC += ./src/main.c
SRC += ./src/rcc.c
SRC += ./src/gpio_dr.c
SRC += ./src/timer_dr.c
SRC += ./src/ISR.c
SRC += ./src/ext_int.c

#providing necessary Library for linker with -lgcc
$(OUT):
	arm-none-eabi-gcc -Wall -g -o $(OUT).elf $(CFLAGS) $(SRC) -lgcc  
	arm-none-eabi-objcopy -O binary $(OUT).elf $(OUT).bin
	arm-none-eabi-size $(OUT).elf
	
.PHONY:  clean flash info gdb_server
clean:
	rm $(OUT).elf $(OUT).bin
flash: 
	st-flash --reset write $(OUT).bin 0x8000000
info:
	st-info --probe
gdb_server:
	st-util

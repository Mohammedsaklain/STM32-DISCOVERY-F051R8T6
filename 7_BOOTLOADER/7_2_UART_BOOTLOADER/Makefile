# file : Makefile
# Date : 17/05/25 - 15:00

# Compiler & Linker
CC 		= arm-none-eabi-gcc
LD 		= arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE	= arm-none-eabi-size
OBJDUMP = arm-none-eabi-objdump

# Outupt
OUTPUT 	= UART_BOOT_app_code

# Directories
BUILD_DIR	= build
SRC_DIR		= src
INC_DIRS	= -I. -Iinc -Idrivers
BOOTLOADER_BIN_DIR = build

# Source & Object files
SRC = stm32f051r8_startup.c
SRC+= ext_int.c
SRC+= flash.c
SRC+= gpio_dr.c
SRC+= main.c
SRC+= rcc.c
SRC+= uart.c
#SRC+= $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o, $(notdir $(SRC)))

# Flags
# Optimization levels: -O0, -O1, -O2, -O3, -Os, -Ofast, -Og
CFLAGS 	= -g -mlittle-endian -mthumb -mcpu=cortex-m0 -mthumb-interwork -mfloat-abi=soft \
			$(INC_DIRS) -O0 -ffunction-sections -fdata-sections# -nostdlib
LDFLAGS = -T stm32f051r8.ld -Wl,-Map=$(BUILD_DIR)/$(OUTPUT).map -lm -lgcc
# -lm (for math functions) & -lgcc (for compiler support functions like integer division/multiplication)

# Help make find the sources
vpath %.c $(SRC_DIR)

all: $(BUILD_DIR)/$(OUTPUT).elf
	@ echo "Building...$(OUTPUT).elf"
	@ echo "Build Successfull"

# C to OBJ
$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(BUILD_DIR)
	@ echo "Compiling $<"
	@ $(CC) -c $(CFLAGS) $< -o $@

# OBJ to ELF
$(BUILD_DIR)/$(OUTPUT).elf: $(OBJ)
	@ echo "Linking $@"
	@ $(LD) $^ $(LDFLAGS) -o $@
	@ echo "Creating binary file $(BUILD_DIR)/$(OUTPUT).bin"
	@ $(OBJCOPY) -O binary $@ $(BUILD_DIR)/$(OUTPUT).bin
	@ echo "--- objdump .text section ---" > $(BUILD_DIR)/$(OUTPUT).text.symbols.txt
	@ $(OBJDUMP) -t $@ | grep .text >> $(BUILD_DIR)/$(OUTPUT).text.symbols.txt
	@ echo "--- End objdump ---" >> $(BUILD_DIR)/$(OUTPUT).text.symbols.txt
	@ echo "Size information for $@"
	@ $(SIZE) $@

# Clean files
clean:
	@ echo "Cleaning build directory..."
	@ rm -f $(BUILD_DIR)/$(OUTPUT).bin $(BUILD_DIR)/$(OUTPUT).elf $(BUILD_DIR)/$(OUTPUT).map
	@ rm -f $(wildcard $(BUILD_DIR)/*.o)
	@ rm -f $(wildcard $(BUILD_DIR)/*.txt)

# Flash the application to its designated address (0x08004000)
flash: $(BUILD_DIR)/$(OUTPUT).bin
	@ echo "Flashing application to 0x08004000..."
	@ st-flash --reset write $(BUILD_DIR)/$(OUTPUT).bin 0x08004000
# This below command is usefull under Low power modes, when DBG & program interface of uC is shutdown
#	st-flash --connect-under-reset write $(BUILD_DIR)/$(OUTPUT).bin 0x08000000
	@ echo "Application flashing complete."

info:
	st-info --probe

gdb_server:
	st-util

.PHONY: all clean flash info gdb_server
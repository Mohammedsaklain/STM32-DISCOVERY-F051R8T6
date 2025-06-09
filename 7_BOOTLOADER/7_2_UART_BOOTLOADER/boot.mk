# file : boot.mk
# Date : 21/05/25 - 12:32

# Compiler & Linker
CC 		= arm-none-eabi-gcc
LD 		= arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE	= arm-none-eabi-size

# Outupt
OUTPUT 	= boot_code

# Directories
BUILD_DIR	= build
SRC_DIR		= src
INC_DIRS	= -I. -Iinc -Idrivers
BOOTLOADER_BIN_DIR = build

# Source & Object files
SRC = STM32_bootloader.c
SRC+= main.c
SRC+= flash.c
SRC+= gpio_dr.c
SRC+= rcc.c
SRC+= uart.c
SRC+= ext_int.c
#SRC+= $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o, $(notdir $(SRC)))

# Flags
CFLAGS 	= -g -mlittle-endian -mthumb -mcpu=cortex-m0 -mthumb-interwork -mfloat-abi=soft \
			$(INC_DIRS) -O0 -ffunction-sections -fdata-sections#-nostdlib 
LDFLAGS = -T bootloader.ld -DBOOTLOADER -Wl,-Map=$(BUILD_DIR)/$(OUTPUT).map -lm -lgcc

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
	@ $(LD) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@ echo "Creating binary file $(BUILD_DIR)/$(OUTPUT).bin"
	@ $(OBJCOPY) -O binary $@ $(BUILD_DIR)/$(OUTPUT).bin
	@ echo "Size information for $@"
	@ $(SIZE) $@

# Clean files
clean:
	@ echo "Cleaning build directory..."
	@ rm -f $(BUILD_DIR)/$(OUTPUT).bin $(BUILD_DIR)/$(OUTPUT).elf $(BUILD_DIR)/$(OUTPUT).map
	@ rm -f $(wildcard $(BUILD_DIR)/*.o)
	@ rm -f $(BUILD_DIR)/combined_flash.bin 
	@ rm -f $(wildcard $(BUILD_DIR)/*.txt)

# Flash only the bootloader to its designated address (0x08000000)
flash: $(BUILD_DIR)/$(OUTPUT).bin
	@ echo "Flashing bootloader to 0x08000000..."
	@ st-flash --reset write $(BUILD_DIR)/$(OUTPUT).bin 0x08000000
	@ echo "bootloader flashing complete."

info:
	st-info --probe

gdb_server:
	st-util

.PHONY: all clean flash info gdb_server
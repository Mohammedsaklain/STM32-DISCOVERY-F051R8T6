# file : Makefile
# Date : 17/05/25 - 15:00

# Compiler & Linker
CC 		= arm-none-eabi-gcc
LD 		= arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE	= arm-none-eabi-size

# Outupt
OUTPUT 	= UNIT_TESTING

# Directories
BUILD_DIR	= app_build
SRC_DIR		= src
INC_DIRS	= -I. -Iinc -Idrivers

# Source & Object files
SRC = stm32f051r8_startup.c
SRC+= $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o, $(notdir $(SRC)))

# Flags
CFLAGS 	= -mlittle-endian -mthumb -mcpu=cortex-m0 -mthumb-interwork -mfloat-abi=soft \
		  -mfpu=fpv4-sp-d16 -nostdlib $(INC_DIRS)
LDFLAGS = -T stm32f051r8.ld -Wl,-Map=$(BUILD_DIR)/$(OUTPUT).map

# Help make find the sources
vpath %.c $(SRC_DIR)

all: $(BUILD_DIR)/$(OUTPUT).elf
	@ echo "Building..."
	@ echo "Build Successfull"

# C to OBJ
$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(BUILD_DIR)
	@ $(CC) -c $(CFLAGS) $< -o $@

# OBJ to ELF
$(BUILD_DIR)/$(OUTPUT).elf: $(OBJ)
	@ $(LD) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@ $(OBJCOPY) -O binary $@ $(BUILD_DIR)/$(OUTPUT).bin
	@ $(SIZE) $@

# Clean files
clean:
	rm -f $(BUILD_DIR)/$(OUTPUT).bin $(BUILD_DIR)/$(OUTPUT).elf $(BUILD_DIR)/$(OUTPUT).map
	rm -f $(wildcard $(BUILD_DIR)/*.o)

flash:
	st-flash --reset write $(BUILD_DIR)/$(OUTPUT).bin 0x8000000

info:
	st-info --probe

gdb_server:
	st-util

.PHONY: all clean flash info gdb_server
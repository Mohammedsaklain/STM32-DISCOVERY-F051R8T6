# file : Makefile - Bootloader
# Date : 11/06/25

# Tools
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size
OBJDUMP = arm-none-eabi-objdump

# Output
OUTPUT  	= OTA
BUILD_DIR 	= build
SRC_DIR 	= src
LINKER_DIR	= linker
INC_DIRS 	= -Iinc -Idrivers

# Source & Object files
SRC = STM32_bootloader.c rcc.c flash.c main.c uart.c
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o, $(notdir $(SRC)))

# Flags 
CFLAGS 	= -g -mlittle-endian -mthumb -mcpu=cortex-m0 -mthumb-interwork -mfloat-abi=soft \
			-ffunction-sections -fdata-sections $(INC_DIRS) -nostdlib -O0 -Wall -Wextra
LDFLAGS = -T $(LINKER_DIR)/bootloader.ld -Wl,-Map=$(BUILD_DIR)/$(OUTPUT).map -Wl,--gc-sections -Wl,--as-needed -lm -lgcc

# Help make find the sources
vpath %.c $(SRC_DIR)

all: $(BUILD_DIR)/$(OUTPUT).elf
	@echo "Build Successful: $(BUILD_DIR)/$(OUTPUT).elf"
	@echo "Size information:"
	@$(SIZE) -B $(BUILD_DIR)/$(OUTPUT).elf

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
	@ echo "Generating symbol table $(BUILD_DIR)/$(OUTPUT).text.symbols.txt"
	@ echo "--- objdump .text section ---" > $(BUILD_DIR)/$(OUTPUT).text.symbols.txt
	@ $(OBJDUMP) -t $@ | grep .text >> $(BUILD_DIR)/$(OUTPUT).text.symbols.txt

# Clean files
clean:
	@echo "Cleaning build directory..."
	@rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(BUILD_DIR)/*.bin $(BUILD_DIR)/*.elf \
	       $(BUILD_DIR)/*.map $(BUILD_DIR)/*.txt $(BUILD_DIR)/*.dis

# Flash the application to its designated address (0x08000000)
flash: $(BUILD_DIR)/$(OUTPUT).bin
	@ echo "Flashing application to 0x08000000..."
	@ st-flash --reset write $(BUILD_DIR)/$(OUTPUT).bin 0x08000000
	@ echo "Application flashing complete."

# Probe information
info:
	@st-info --probe
	@echo "Section sizes for $(BUILD_DIR)/$(OUTPUT).elf:"
	@$(SIZE) -A $(BUILD_DIR)/$(OUTPUT).elf 2>/dev/null || echo "No ELF file found"

# Start GDB server
gdb_server:
	@st-util

# Phony targets
.PHONY: all clean flash info gdb_server
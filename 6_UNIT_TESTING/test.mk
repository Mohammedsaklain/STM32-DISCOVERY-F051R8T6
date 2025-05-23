# file: test.mk
# Date: 17/05/25

# Host Compiler
CC = gcc

# Directories
SRC_DIR       = src
SRC_INC		  = drivers
TEST_SRC_DIR  = unit_test/test
UNITY_DIR     = unit_test/Unity/src
TEST_INC_DIR  = unit_test/test_inc
TEST_BUILD    = unit_test/test_build

# Files
SRC_FILES  = $(SRC_DIR)/rcc.c
TEST_FILES = $(wildcard $(TEST_SRC_DIR)/*.c)
UNITY_SRC  = $(UNITY_DIR)/unity.c
OUTPUT     = $(TEST_BUILD)/RESULT

# Flags
CFLAGS  = -Wall -Wextra -std=c99 -DUNIT_TEST
INCLUDES = -I$(UNITY_DIR) -I$(SRC_INC) -I$(TEST_INC_DIR) -Iinc

# build
all:
	mkdir -p $(TEST_BUILD)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_FILES) $(TEST_FILES) $(UNITY_SRC) -o $(OUTPUT)

run:
	$(TEST_BUILD)/RESULT.exe

clean:
	rm -rf $(TEST_BUILD)/RESULT.exe

.PHONY: all run clean

# TO run   - make -f test.mk
# To clean - make clean -f test.mk

# make -f test.mk tells the make to use different file for it's configuration(test.mk)
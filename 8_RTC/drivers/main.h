/*  pragma once is a preprocessor directive, used to prevent \
    header files from being included multiple times. Same as \
    #ifndef,#define and #endif -> pragma sometimes improve   \
    compilation speed */

#pragma once

#undef BOOTLOADER
#define HOST_UNIT_TEST

#ifdef HOST_UNIT_TEST
    #include "test_stm32f0xx.h"
    #include "unity.h"
    int origin(void);
#else
    #include "stm32f0xx.h"
    int main(void);
#endif

#ifdef BOOTLOADER
    #include "core_cm0.h"
    #include "boot.h"
#endif

#include "rcc.h"
#include "gpio_dr.h"
#include "lcd.h"
#include <stdbool.h>
#include "rtc.h"
#include <stdint.h>

/*  pragma once is a preprocessor directive, used to prevent \
    header files from being included multiple times. Same as \
    #ifndef,#define and #endif -> pragma sometimes improve   \
    compilation speed */

#pragma once

#undef HOST_UNIT_TEST

#ifdef HOST_UNIT_TEST
    #include "test_stm32f0xx.h"
#else
    #include "stm32f0xx.h"
#endif

#include "rcc.h"
#include "gpio_dr.h"
#include "lcd.h"
#include <stdint.h>

int main(void);

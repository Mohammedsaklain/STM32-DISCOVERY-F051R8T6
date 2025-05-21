/*  pragma once is a preprocessor directive, used to prevent \
    header files from being included multiple times. Same as \
    #ifndef,#define and #endif -> pragma sometimes improve   \
    compilation speed */

#pragma once

#include "rcc.h"
#include "gpio_dr.h"
#include "lcd.h"
#include "core_cm0.h"
#include "boot.h"
#include "stm32f0xx.h"
#include <stdbool.h>

int main(void);

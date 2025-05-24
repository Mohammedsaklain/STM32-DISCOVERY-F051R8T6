/*  pragma once is a preprocessor directive, used to prevent \
    header files from being included multiple times. Same as \
    #ifndef,#define and #endif -> pragma sometimes improve   \
    compilation speed */

#pragma once

#define UART_PRINTF     /* To include UART Print Debug Function*/
#undef BOOTLOADER       /* To implement the Bootloader code*/
#undef HOST_UNIT_TEST   /* Unit testing using UNITY framework*/

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

/* Custom headers */
#include "rcc.h"
#include "gpio_dr.h"
#include "lcd.h"
#include "rtc.h"
#include "uart.h"
/* Standard headers */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

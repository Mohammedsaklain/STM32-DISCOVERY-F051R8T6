/*  pragma once is a preprocessor directive, used to prevent \
    header files from being included multiple times. Same as \
    #ifndef,#define and #endif -> pragma sometimes improve   \
    compilation speed */

#pragma once

#define UART_PRINTF     /* To include UART Print Debug Function*/
#define BOOTLOADER       /* To implement the Bootloader code*/
#undef HOST_UNIT_TEST   /* Unit testing using UNITY framework*/


#include <stdint.h>
#include <stdbool.h>

#ifdef HOST_UNIT_TEST
    #include "test_stm32f0xx.h"
    #include "unity.h"
    int origin(void);
#endif
#ifdef BOOTLOADER
    #include "stm32f0xx.h"
    #include "boot.h"
    int main(void);
#endif
#ifdef UART_PRINTF
    /* CMSIS */
    #include "core_cm0.h"
    /* Standard headers */
    #include <stdlib.h>
    #include <stdarg.h>
    #include <string.h>
    #include <stdio.h>
#endif

/* Custom headers */
#include "rcc.h"
#include "gpio_dr.h"
#include "lcd.h"
#include "rtc.h"
#include "uart.h"
#include "ext_int.h"
#include "low_pwr_md.h"
#include "flash.h"
#include "systick.h"


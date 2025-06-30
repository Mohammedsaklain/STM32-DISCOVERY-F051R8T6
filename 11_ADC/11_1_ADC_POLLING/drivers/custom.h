#ifndef CUSTOM_H_
#define CUSTOM_H_

#include "stm32f0xx.h"
#include "core_cm0.h"
#include <stdint.h>
//#include <stdarg.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <string.h>
#include <stdio.h>

#define UART_PRINTF
#undef BOOTLOADER
#undef HOST_UNIT_TEST       /* Unit testing using UNITY framework*/
#undef SYSTICK_REQ

#ifdef HOST_UNIT_TEST
    #include "test_stm32f0xx.h"
    #include "unity.h"
    int origin(void);
#endif
#ifndef BOOTLOADER
    int main(void);
#endif

#endif
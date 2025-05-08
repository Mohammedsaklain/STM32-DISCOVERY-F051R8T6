#ifndef MAIN_H
#define MAIN_H


#include "rcc.h"
#include "gpio_dr.h"
#include "stm32f0xx.h"
#include "timer_dr.h"
#include "uart.h"

uint32_t RF_DATA_READ(uint32_t time_interval);

int main(void);

#endif
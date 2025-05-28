## Low Power Modes

### Project AIM:
1. To operate in Sleep, Stop and Standby Mode

### Setup

1. I'm using Discovery board - STM32F0R8T6 with FLUKE DMM for current measurement. The DMM gives approximate values which is enough to evaluate the working of Low power modes.
2. The onboard JP2 connector provides the option for current measurement, we can connect ammeter to measure the current consumption. If we remove jumper JP2, then the controller will not work until reconnected JP2 Jumper or use ammeter. 

* The STM32 features 3 low power modes:
1. Sleep mode (CPU clock off, all peripherals including Cortex®-M0 core peripherals like NVIC, SysTick, etc. are kept running)
2. Stop mode (all clocks are stopped)
3. Standby mode (1.8V domain powered-off)

## 1. Sleep Mode:<br>
The Sleep mode is entered by executing the WFI (Wait For Interrupt) or WFE (Wait for Event) instructions. Two options are available to select the Sleep mode entry mechanism, depending on the SLEEPONEXIT bit in the Cortex®-M0 System Control register:

### Wait for interrupt(WFI): The CPU enters low-power mode and wakes up when any enabled interrupt occurs
* Interrupt must be enabled in NVIC.
* ISR will run after wakeup.
* Commonly used with EXTI, timers, USART, etc.
``` C
    __WFI(); // Wait for an Interrupt or 
```
1. Sleep-now: if the SLEEPONEXIT bit is cleared in SCR(System Control Register), the MCU enters Sleep mode as soon as WFI or WFE instruction is executed. The SCB register definitions can be found in the core_cm0.h file and programming manual for the device.
``` C
    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
    __WFI();
```
2. Sleep-on-exit: if the SLEEPONEXIT bit is set, the MCU enters Sleep mode as soon as it exits the lowest priority ISR. 
``` C
    SCB->SCR |=  SCB_SCR_SLEEPONEXIT_Msk;
```

### Wait for Event(WFE): The CPU sleeps until an event occurs
The events can come from, an Interrupt being pending even if it is not enabled or from the software generated event(via __SEV()).__SEV() sends an event signal to the CPU and if the CPU is sleeping in __WFE(), then it wakes up. WFE is usefull when you want to signal another part of your code (or core) that something has happened, but don’t want to use an interrupt. This mode offers the lowest wake-up time as no time is wasted in interrupt entry/exit<br>

Why should use WFE instead of interrupts<br>
1. More manual control
2. Lets you create RTOS like behavious
3. Avoids entering ISR unless absolutely needed.
``` C
    /* Example usage */
    while(!flag){
        __WFE(); // Sleep until flag is set
    }

    // From another part of code, which require waking up of CPU
    flag = 1;
    __SEV();    // send event to Wake up CPU
    /* Here after changing the flag=1, and program wants to wake up the CPU, 
    then it calls __SEV() for it */
```
4. Note: after reset or boot, the event register is set to 0, which makes WFE not usable, so follow :
``` C
    __SEV();    // Set the event register
    __WFE();    // clear event register
    __WFE();    // Now wait until a new event occurs
```

### Observations in Sleep Mode:
1. The existing application code without sleep mode consumes approximately ***3.03mA*** which has GPIOA & C, USART2, SYSCFG and PWR clocks enabled. To further reduce power consumption in Sleep mode the peripheral clocks can be disabled prior to executing the WFI or WFE instructions.
2. Enabling the sleep mode, it consumes around ***1.18mA***

## 2. Stop Mode:

To enter into Stop mode either by WFI or WFE, follow below steps

1. Set *SLEEPDEEP* bit in Cortex-M0 system control register<br>
2. Clear *PDDS* bit in Power Control register (PWR_CR)<br>
3. Select the voltage regulator mode by configuring *LPDS bit* in PWR_CR<br>

``` C
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    PWR->CR &= ~PWR_CR_PDDS;
    PWR->CR &= ~PWR_CR_LPDS;
```
To wake up from Stop Mode, Use below options:

1. Any EXTI line configured in Interrupt mode (the corresponding EXTI 
Interrupt vector must be enabled in the NVIC).
2. Some specific communication peripherals (CEC, USART, I2C) interrupts, 
when programmed in wake-up mode (the peripheral must be 
programmed in wake-up mode and the corresponding interrupt vector 
must be enabled in the NVIC).<br>

### Observations in Stop Mode:
1. The stop mode of operation consumes approximately ***0.33mA*** of current with Voltage regulator On during Stop mode.
2. No significant changes observed when Voltage regulator in low power mode, ***~0.31mA***

## 3. Standby Mode: 

To enter into Standy mode either by WFI or WFE, follow below steps

1. Set *SLEEPDEEP* in Cortex®-M0 System Control register
2. Set *PDDS* bit in Power Control register (PWR_CR)
3. Clear *WUF* bit in Power Control/Status register (PWR_CSR)
4. If used Wakeup pin, Select Wake up pin

``` C
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;      // Set to Deep Sleep Mode
    PWR->CR |=  PWR_CR_PDDS;                // Enter Standby mode when the CPU enters Deepsleep
    PWR->CSR |= PWR_CSR_EWUP1;              // Select the Wake Up pin - PA0
    PWR->CR |= PWR_CR_CWUF;                 // Clear WUF - Wake up flag
    PWR->CSR&= ~PWR_CSR_WUF;                // it shows wether wakeup event was occured previously, it can be cleared directly or using CWUF flag in PWR->CR 
    PWR->CR |= PWR_CR_CSBF;                 // Clear standby flag
```
To exit from Standby Mode, 

* WKUP pin rising edge, RTC alarm event’s rising edge, external Reset in NRST pin, IWDG Reset.

### Observations in Standby Mode:
1. The Current consumption was significantly reduced, approximately ***4.9uA***

### In summary:

| Mode | Current Consumption |
|---|---|
| No Power save mode| 3.03mA |
| Sleep | 1.18 mA |
| Stop | 0.33mA |
| Standby | 4.9uA |
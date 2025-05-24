# External Interrupt & Events

1. *External Interrupt:* When an edge (rising, falling, or both) occurs on a selected EXTI line, it generates an interrupt request to the NVIC. If enabled in the NVIC, this will halt the CPU's current execution, jump to the corresponding Interrupt Service Routine (ISR), and execute the code within the ISR.<br>
2. *External Event:* When an edge occurs on a selected EXTI line, it generates an event pulse. This pulse is typically used to "Wake up the CPU from Stop or Standby low-power modes", "Trigger peripherals directly (e.g., start a DMA transfer, trigger a timer, trigger an ADC conversion)". This happens without an ISR, saving CPU cycles and latency

## Interrupts

1. Enalbe the SYSCFG bit(System Configuration) in APB2ENR register, which does Managing the external interrupt line connection to the GPIOs(The SYSCFG handles other required operation also, read reference manual for more info)
``` C
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
```
2. ***Hardware interrupt selection:***

To configure a line as interrupt source, use the following procedure:<br>
 • Select correct pin for the external interrupt from EXTICR register
 • Configure the corresponding mask bit in the EXTI_IMR register.
 • Configure the trigger selection bits of the interrupt line (EXTI_RTSR and EXTI_FTSR)
 • Configure the enable and mask bits that control the NVIC IRQ channel mapped to the EXTI so that an interrupt coming from one of the EXTI line can be correctly acknowledged.
``` C
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;   // PA0
    EXTI->IMR |= EXTI_IMR_MR0;      // Mask line 0
    EXTI->FTSR &= ~EXTI_FTSR_TR0;   // Disable falling edge on line 0
    EXTI->RTSR |= EXTI_RTSR_TR0;    // Enalbe rising edge on line 0 
    NVIC_EnableIRQ(EXTI0_1_IRQn);
```

3. ***Hardware event selection***

To configure a line as event source, use the following procedure:<br>
 • Configure the corresponding mask bit in the EXTI_EMR register.
 • Configure the Trigger Selection bits of the Event line (EXTI_RTSR and EXTI_FTSR)
``` C
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;   // PA0
    EXTI->FTSR &= ~EXTI_FTSR_TR0;                   // Disable falling edge on line 0
    EXTI->RTSR |= EXTI_RTSR_TR0;                    // Enalbe rising edge on line 0 
    EXTI->EMR |= EXTI_EMR_MR0;                      // Event mask register
    EXTI->IMR &= ~(EXTI_IMR_MR0);                   // Disable Interrupt generation 
    EXTI->PR |= (EXTI_PR_PR0);                      // Clear the interrupt flag, Note: Writing 1, clears the flag
```
***NOTE:*** For application use of External Event, Follow the Low Power Modes project

4. ***Software interrupt/event selection***
Any of the external lines can be configured as software interrupt/event lines. The following is the procedure to generate a software interrupt.<br>
 • Configure the corresponding mask bit (EXTI_IMR, EXTI_EMR)
 • Set the required bit of the software interrupt register (EXTI_SWIER)
/* file: gpio_dr.c */

#include "custom.h"
#include "gpio_dr.h"

/* Enable clock for selected GPIO */
void GPIO_Clock_Enable(GPIO_TypeDef *PORT){
    if(PORT==GPIOA) RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    else if(PORT==GPIOB) RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    else if(PORT==GPIOC) RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    else if(PORT==GPIOD) RCC->AHBENR |= RCC_AHBENR_GPIODEN;
    else if(PORT==GPIOE) RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
}

/* To Initialize GPIO Pin*/
int8_t GPIO_Init(GPIO_TypeDef *PORT, uint8_t pin, uint8_t mode, uint8_t output_type, uint8_t speed, uint8_t pupd){
    if(pin>15 || mode>ANALOG || output_type>OPEN_DRAIN || speed>HIGH_SPEED || pupd>PDOWN){
        return -1;                          // Invalid parameters
    }

    GPIO_Clock_Enable(PORT);                // Enable GPIO Clock

    PORT->MODER &= ~(3U<<(pin*2));          // clear pin 
    PORT->MODER |= ((mode)<<(pin*2));       // Set the PIN mode

    PORT->OTYPER &= ~(1U<<pin);             // Clear Output Type
    PORT->OTYPER |= (output_type<<pin);     // Output type - Push-Pull / Open Drain

    PORT->OSPEEDR &= ~(3U<<(pin*2));        // Clear GPIO speed
    PORT->OSPEEDR |= (speed<<(pin*2));      // set GPIO speed

    PORT->PUPDR &= ~(3U<<(pin*2));          // Clear bits
    PORT->PUPDR |= ((pupd)<<(pin*2));       // Pull Up/Down

    return 0;
}

/* To set Alternate function */
int8_t GPIO_Set_Alternate_Function(GPIO_TypeDef *PORT, uint8_t pin, uint8_t af){

    if(pin>15 || af>AF7){
        return -1;
    }

    PORT->MODER &= ~(3U<<(pin*2));           // clear pin 
    PORT->MODER |=  (af<<(pin*2));           // Alternate Function

    if(pin<=7){
        PORT->AFR[0]|= (af<<(pin*4));
    }
    else{
        PORT->AFR[1]|= (af<<(pin*4));
    }
    return 0;                               // If program comes here, means error
}

/* To set pin as Digital Output*/
/* The function expects a pointer (*PORT) to a struct (GPIO_TypeDef)*/
int8_t GPIO_Digital_Out(GPIO_TypeDef *PORT, uint8_t pin){
    if(pin>15){
        return -1;
    }
    return GPIO_Init(PORT, pin, OUT, PUSH_PULL, HIGH_SPEED,NO_PUPD); 
}

/* Write Pin level*/
int8_t GPIO_Write(GPIO_TypeDef *PORT, uint8_t pin, uint8_t level){
    if(pin>15 || level>HIGH){
        return -1;
    }

    if(level==HIGH){
        PORT->BSRR = (1U<<pin);         // Set 
    }else{
        PORT->BSRR = (1U<<(pin+16));    // Reset
    }
    return 0;
}

/* Toggle GPIO pin */
int8_t GPIO_Toggle(GPIO_TypeDef *PORT, uint8_t pin){
    if(pin>15){
        return -1;
    }

    PORT->ODR ^= (1U<<pin);
    return 0;
}

/* Read Pin Level*/
int8_t Gpio_Read(GPIO_TypeDef *PORT, uint8_t pin){
    if(pin>15){
        return -1;
    }
    return (PORT->IDR >> pin) & 0x01;
}

/* Reset GPIO pin to default state */
/* Default: input, no pullup/down */
int8_t GPIO_Reset(GPIO_TypeDef *PORT, uint8_t pin){
    if(pin>15){
        return -1;
    }
    return GPIO_Init(PORT, pin, IN, PUSH_PULL, LOW_SPEED, NO_PUPD);
}

int8_t GPIO_Configure_Interrupt(GPIO_TypeDef *PORT, uint8_t pin, uint8_t trigger){
    if(pin>15 || trigger > BOTH){
        return -1;
    }

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;   /* Enable SYSCFG clock */
    uint8_t port_num = ((uint32_t)PORT - (uint32_t)GPIOA)/((uint32_t)GPIOB-(uint32_t)GPIOA);  /* assume GPIOA=400,GPIOB=500...*/

    /* Map GPIO to EXTI line */
    if(pin<=3)      SYSCFG->EXTICR[0] |= (port_num<<(pin*4));
    else if(pin<=7) SYSCFG->EXTICR[1] |= (port_num<<(pin*4));
    else if(pin<=11)SYSCFG->EXTICR[2] |= (port_num<<(pin*4));
    else if(pin<=15)SYSCFG->EXTICR[3] |= (port_num<<(pin*4));

    /* Configure Trigger */
    EXTI->IMR |= (1U<<pin);                         // Enable Interrupt
    EXTI->RTSR &= ~(1U<<pin);                       // Clear rising edge trigger
    EXTI->FTSR &= ~(1U<<pin);                       // Clear falling edge trigger
    if(trigger==RISING || trigger==BOTH){
        EXTI->RTSR |= (1U<<pin);                    // Enable rising edge
    }
    if(trigger==FALLING || trigger==BOTH){
        EXTI->FTSR |= (1U<<pin);                    // Enable falling edge
    }

    /* Enable NVIC */
    uint8_t irq;
    if(pin<2)       irq = EXTI0_1_IRQn;
    else if(pin<4)  irq = EXTI2_3_IRQn;
    else if(pin<15) irq = EXTI4_15_IRQn;

    NVIC_EnableIRQ(irq);
    return 0;
}

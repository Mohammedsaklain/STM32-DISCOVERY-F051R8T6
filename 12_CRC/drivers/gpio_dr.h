#ifndef GPIO_DR_H_
#define GPIO_DR_H_

#define HIGH 1
#define LOW  0

enum gpio_mode
{IN,OUT,AF,ANALOG};

enum gpio_pullup_down
{NO_PUPD,PUP,PDOWN};

enum gpio_af
{AF0,AF1,AF2,AF3,AF4,AF5,AF6,AF7};

enum gpio_speed
{LOW_SPEED, MEDIUM_SPEED, HIGH_SPEED=3};

enum gpio_output_type
{PUSH_PULL, OPEN_DRAIN};

enum int_trigger
{RISING, FALLING, BOTH};

void GPIO_Clock_Enable(GPIO_TypeDef *PORT);
int8_t GPIO_Init(GPIO_TypeDef *PORT, uint8_t pin, uint8_t mode, uint8_t output_type, uint8_t speed, uint8_t pupd);
int8_t GPIO_Set_Alternate_Function(GPIO_TypeDef *PORT, uint8_t pin, uint8_t af);
int8_t GPIO_Digital_Out(GPIO_TypeDef *PORT, uint8_t pin);
int8_t GPIO_Write(GPIO_TypeDef *PORT, uint8_t pin, uint8_t level);
int8_t GPIO_Toggle(GPIO_TypeDef *PORT, uint8_t pin);
int8_t Gpio_Read(GPIO_TypeDef *PORT, uint8_t pin);
int8_t GPIO_Reset(GPIO_TypeDef *PORT, uint8_t pin);
int8_t GPIO_Configure_Interrupt(GPIO_TypeDef *PORT, uint8_t pin, uint8_t trigger);

#endif
#ifndef GPIO_H_
#define GPIO_H_

#define HIGH 1
#define LOW  0
void Digital_Out(GPIO_TypeDef *PORT, uint8_t pin);
void Gpio_Write(GPIO_TypeDef *PORT, uint8_t pin, uint8_t level);
#endif
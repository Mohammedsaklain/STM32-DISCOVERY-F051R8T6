#include "uart.h"
#include "custom.h"
#include "gpio_dr.h"

/* UART GPIO Initialization*/
void GPIO_UART_Init(void){
    GPIOA->MODER &= ~((3<<4) | (3<<6));     // Clear bits
    GPIOA->MODER |= (2<<4) | (2<<6);        // Selecting PA2(TX) & PA3(RX) as alternate function
    GPIOA->AFR[0] &= ~((1<<8) | (1<<12));   // Clear Bits
    GPIOA->AFR[0] |= (1<<8) | (1<<12);      // Alternate function register - AF1 for PA2 & PA3
    GPIOA->OSPEEDR &= ~((3<<4) | (3<<6));
    GPIOA->OSPEEDR |= ((3<<4) | (3<<6));    // High Speed mode
}

void UART_Init(void)
{
    /* Reset required bits in USART2_CR1*/
    USART2->CR1 &=~((1<<28) |           // M1
                    (1<<12) |           // M0
                    (1<<15));           // OVER Sampling by 16
    /* Set required bits in USART2_CR1*/
    USART2->CR1 |=  (USART_CR1_TE       // Enable Transmitter
                    |USART_CR1_RE       // Enable Receiver
                    |USART_CR1_UE);     // Enable UART2
    /* Reset required bits in USART2_CR2*/
    USART2->CR2 &=~ (3<<12);            // 1 Stop bit
    USART2->BRR |= 69;                  // BD at 115200
    GPIO_UART_Init();
}

void UART_Send_Data(uint8_t data)
{
    /* Wait until TRANSMIT DATA REGISTER is ready to take data*/
    while(!((USART2->ISR) & (USART_ISR_TXE)));
    // Simply send the data through TDR, when it's ready
    USART2->TDR = data; 
}

uint8_t UART_Receive_Data(void){

    while(1){
        /* Check if there is a data in RECEIVE DATA REGISTER*/
        while(!((USART2->ISR) & (USART_ISR_RXNE))){}
        uint32_t status_reg = USART2->ISR;

        if(status_reg & (USART_ISR_ORE | USART_ISR_NE | USART_ISR_FE)){
        (void)USART2->RDR;
            continue;
        }
        uint8_t rxData = (USART2->RDR & 0xFF);
        return rxData;    
    }
}


void UART_Send_String(char *string){
    while (*string){
        UART_Send_Data(*string ++);
    }
}

#ifdef UART_PRINTF

// Used compiler builtins instead of <stdarg.h>
typedef __builtin_va_list va_list;
#define va_start(v, l) __builtin_va_start(v, l)
#define va_arg(v, t)   __builtin_va_arg(v, t)
#define va_end(v)      __builtin_va_end(v)

int __io_putchar(int ch) {
    if (ch == '\n') {
        UART_Send_Data('\r');
    }
    UART_Send_Data((uint8_t)ch);
    return ch;
}

static void print_string(const char *s) {
    while (*s) {
        if (*s == '\n') {
            UART_Send_Data('\r');
        }
        UART_Send_Data(*s++);
    }
}

static void print_uint_decimal(unsigned int n) {
    char buf[20];
    int i = 0;
    if (n == 0) {
        UART_Send_Data('0');
        return;
    }
    while (n > 0) {
        buf[i++] = (n % 10) + '0';
        n /= 10;
    }
    while (i > 0) {
        UART_Send_Data(buf[--i]);
    }
}

static void print_int_decimal(int n) {
    if (n < 0) {
        UART_Send_Data('-');
        n = -n;
    }
    print_uint_decimal((unsigned int)n);
}


static void print_uint_hex(unsigned int n) {
    char buf[8];
    int i = 0;
    if (n == 0) {
        UART_Send_Data('0');
        return;
    }
    while (n > 0 || i == 0) {
        int digit = n % 16;
        buf[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
        n /= 16;
        if (n == 0 && i > 0) break;
    }
    while (i > 0) {
        UART_Send_Data(buf[--i]);
    }
}

void MS_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c':
                    UART_Send_Data((uint8_t)va_arg(args, int));
                    break;
                case 's':
                    print_string(va_arg(args, const char *));
                    break;
                case 'd':
                case 'i':
                    print_int_decimal(va_arg(args, int));
                    break;
                case 'x':
                case 'X':
                    print_uint_hex(va_arg(args, unsigned int));
                    break;
                case '%':
                    UART_Send_Data('%');
                    break;
                default:
                    UART_Send_Data('%');
                    if (*format) UART_Send_Data(*format);
                    break;
            }
        } else {
            if (*format == '\n') {
                UART_Send_Data('\r');
            }
            UART_Send_Data(*format);
        }
        format++;
    }

    va_end(args);
}


/* Custom Function to print floating numbers, Only positive without rounding */
void print_float(float Num){

    /* To support Negative Numbers */
    if(Num<0){
        MS_printf("-");
        Num = -Num;
    }

    int unit = (int)Num;             /* Extract the unit part. Ex Num = 1.5 -> unit = 1 */
    float frac = Num - (float)unit;        /* fraction = 1.5 - 1.0 = 0.5 */
    int fraction = (int)(frac * 100 + 0.5); /* Mul by 100 for 2 decimal places. 0.5*100 -> 50*/
    /* for rounding, adding 0.5, ex: 3.149 ->unit =3, fraction =(0.149*100+0.5)->15.4 -> 15 */
    
    MS_printf("%d.%d\r\n",unit,fraction); /* %02d ensures 2 digits for fraction */
}

#endif
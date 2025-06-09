#include "custom.h"
#include "uart.h"
#include "gpio_dr.h"

/* UART - 2 Selection*/
void UART_Init(void)
{
    GPIO_UART_Init();
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
    USART2->BRR = 69;                   // BD at 115200
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




/******************************************************************************/
#ifdef UART_PRINTF
/* This Printf function is a Open Source Project, included to reduce
    the size compare to modifying regular print function.
    for ex: regular printf  - ~(49KB size taken)
            existing printf - ~(8KB  in size)*/

/* This function is often called by minimal printf implementations */
int __io_putchar(int ch) {
    // Handle newline for console readability if desired
    if (ch == '\n') {
        UART_Send_Data('\r');
    }
    UART_Send_Data((char)ch);
    return ch;
}

/*  existing type specifier, %c, %s, %d, %x 
    you can modify or add new types */

/* Helper function to print a string */
static void print_string(const char *s) {
    while (*s) {
        if (*s == '\n') { // Add carriage return for newlines
            UART_Send_Data('\r');
        }
        UART_Send_Data(*s++);
    }
}

/* Helper function to print an unsigned integer in decimal */
static void print_uint_decimal(unsigned int n) {
    char buf[10]; // Max 10 digits for 32-bit uint
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

/* Helper function to print an integer in decimal (handles negative) */
static void print_int_decimal(int n) {
    if (n < 0) {
        UART_Send_Data('-');
        n = -n; // Make positive
    }
    print_uint_decimal((unsigned int)n);
}

/* Helper function to print an unsigned integer in hexadecimal */
static void print_uint_hex(unsigned int n) {
    char buf[8]; // Max 8 hex digits for 32-bit uint
    int i = 0;
    if (n == 0) {
        UART_Send_Data('0');
        return;
    }
    while (n > 0 || i == 0) { // Ensure at least one digit for 0
        int digit = n % 16;
        if (digit < 10) {
            buf[i++] = digit + '0';
        } else {
            buf[i++] = digit - 10 + 'a'; // Use lowercase a-f
        }
        n /= 16;
        if (n == 0 && i > 0) break; // Break if n becomes 0 and we've printed at least one digit
    }
    while (i > 0) {
        UART_Send_Data(buf[--i]);
    }
}

/* Custom print Function*/
void MS_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++; // Move past '%'
            switch (*format) {
                case 'c':
                    UART_Send_Data(va_arg(args, int));
                    break;
                case 's':
                    print_string(va_arg(args, const char *));
                    break;
                case 'd':
                case 'i':
                    print_int_decimal(va_arg(args, int));
                    break;
                case 'x':
                case 'X': // You can make it handle uppercase too
                    print_uint_hex(va_arg(args, unsigned int));
                    break;
                case '%':
                    UART_Send_Data('%');
                    break;
                default:
                    // Unknown format specifier, print it literally
                    UART_Send_Data('%');
                    UART_Send_Data(*format);
                    break;
            }
        } else {
            if (*format == '\n') { // Add carriage return for newlines
                UART_Send_Data('\r');
            }
            UART_Send_Data(*format);
        }
        format++;
    }

    va_end(args);
}
#endif
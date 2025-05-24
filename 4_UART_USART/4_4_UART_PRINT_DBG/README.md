## UART printf function implementation:

1. Create a basic UART transmit function which transmit single character at a time.
``` C
    void UART_Send_Data(uint8_t data)
    {
        while(!(USART2->ISR & USART_ISR_TXE));
        USART2->TDR = data; 
    }
```
2. Implement a Simple _putc or __io_putchar Function
``` C
    int __io_putchar(int ch) {
    // Handle newline for console readability if desired
        if (ch == '\n') {
            UART_Send_Data('\r');
        }
        UART_Send_Data((char)ch);
        return ch;
    }
```
3. Implement your printf function. You can find many minimalist printf implementations online. A popular one is printf.c by Kustaa Nyholm (often used in embedded projects). The printf function used here is also a inspiration from one of the open source project.

``` C
    /*  existing type specifier, %c, %s, %d, %x, you can modify or add new types */
    
    /* Helper function to print a string */
    static void print_string(const char *s);

    /* Helper function to print an unsigned integer in decimal */
    static void print_uint_decimal(unsigned int n);

    /* Helper function to print an integer in decimal (handles negative) */
    static void print_int_decimal(int n);

    /* Helper function to print an unsigned integer in hexadecimal */
    static void print_uint_hex(unsigned int n);

    /* Custom print Function*/
    void MS_printf(const char *format, ...);
```
4. Use in the main application<br>
``` C
    int a = 2;
    MS_printf("Hello from main %d",a);
```
#include "usart.h"

void usart_init(uint16_t ubrr)
{
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    /*Asynchronous double speed mode */
    UCSR0A |= (1 << U2X0);

    /*Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void usart_transmit(unsigned char byte)
{
    /*Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    /*Put data into buffer, sends the data */
    UDR0 = byte;
}

void usart_transmit_str(unsigned char *array)
{
    while (*array)
    {
        usart_transmit(*array++);
        // array++;
    }
}

unsigned char usart_data_available()
{
    return (UCSR0A & (1 << RXC0));
}

unsigned char usart_receive(void)
{
    /*Wait for data to be received */
    while (!usart_data_available())
        ;

    /*Get and return received data from buffer */
    return UDR0;
}

// void lcd_puts_p(const char *progstr)
// {
//     char c;
//     while ((c = pgm_read_byte(progstr++)))
//     {
//         usart_transmit(c);
//     }
// }
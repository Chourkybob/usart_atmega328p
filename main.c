#include <avr/io.h>
#include <avr/pgmspace.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#include "usart.h"

int main(void)
{
    char byte;
    char msg[] = {"Salut Bonjour\r\n"};

    usart_init(UBRR);

    DDRB |= (1 << DDB5);
    while (1)
    {
        byte = usart_receive();
        if (byte == 'p')
        {
            usart_transmit_str(msg);
        }

        // PORTB |= (1 << PORTB5);
        // _delay_ms(1000);
        // PORTB &= ~(1 << PORTB5);
        // _delay_ms(1000);
    }
}
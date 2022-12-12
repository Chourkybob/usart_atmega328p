#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

void usartInit(uint32_t baudRate)
{
 UBRR0L = BAUD_PRESCALE(F_CPU,baudRate);
 UBRR0H = (BAUD_PRESCALE(F_CPU,baudRate) >> 8); 
 UCSR0B = ((1<<TXEN0)|(1<<RXEN0);
 UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}

void usartSendByte(uint8_t data)
{
 while((UCSR0A & (1<<UDRE0)) == 0);
 UDR0 = data;
}

unsigned char usartDataAvailable()
{
 return (UCSR0A & (1<<RXC0));
}

uint8_t usartGetRxByte()
{
 // Option pour attendre la réception d'une donnée... risque de blocage
 // while (!usartDataAvailable());
 return UDR0;
}

void main(void)
{
    usartInit(19200);
    while (1)
    {
        if (usartDataAvailable())
            data = usartGetRxByte();
        usartSendByte(data);
        _delay_ms(1000);
    }
}
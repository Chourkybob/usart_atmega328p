#include <avr/io.h>

#define BAUD_RATE 115200
#define UBRR F_CPU / 8 / BAUD_RATE - 1

void usart_init(uint16_t ubrr);
void usart_transmit(unsigned char byte);
void usart_transmit_str(unsigned char *array);
unsigned char usartDataAvailable();
unsigned char usart_receive(void);
// void lcd_puts_p(const char *progstr);
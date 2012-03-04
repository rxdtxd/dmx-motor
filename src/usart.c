// usart.c

#include "usart.h"

#include <avr/io.h>

#include "transceiver.h"
#include "iocontrol.h"

void usart_init_modbus (void) {
    // set ~RE for transmitter mode
    set_output(USART_DDR, USART_NRE);
    output_high(USART_PORT, USART_NRE);

    // set baud rate (9600 Hz)
    UBRR0H = 0;
    UBRR0L = 103;

    // set frame format: asynchronous, 8 data bits, 2 stop bits, no parity
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01) | _BV(USBS0);

    // enable transmitter
    UCSR0B = _BV(TXEN0);
}


void usart_init_dmx (void) {
    // init databuf (TODO: in function?)
    /* int i; */
    /* for (i = 0; i < sizeof(databuf); i++) databuf[i] = 0; */

    // set ~RE for receiver mode
    set_output(USART_DDR, USART_NRE);
    output_low(USART_PORT, USART_NRE);

    // set baud rate (250 kHz)
    UBRR0H = 0;
    UBRR0L = 3;

    // set frame format: asynchronous, 8 data bits, 2 stop bits, no parity
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01) | _BV(USBS0);

    // enable receiver and interrupt
    UCSR0B = _BV(RXEN0) | _BV(RXCIE0);
}

void usart_stop (void) {
    // wait for empty transmit buffer
    while ( !( UCSR0A & (1<<UDRE0)) );

    UCSR0B = 0;
}

void usart_transmit (uint8_t data) {
    // wait for empty transmit buffer
    while ( !( UCSR0A & (1<<UDRE0)) );
    // put data into the buffer (automatically sends it)
    UDR0 = data;
}

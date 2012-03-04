// dmx dimmer, transceiver module

#ifndef _TRANSCEIVER_H_
#define _TRANSCEIVER_H_

#include <avr/io.h>

// ===== CONFIG =====

#define F_CPU 16000000  // 16 MHz

// ===== PINOUT =====

#define USART_DDR     DDRD   // RS485 DDR for Read Enable (Receiving)
#define USART_RXD_DDR DDD0   // receive
#define USART_TXD_DDR DDD1   // drive/transmit
#define USART_NRE_DDR DDD2   // Active Low Read Enable

#define USART_PORT PORTD
#define USART_TXD  PD1
#define USART_NRE  PD2

#define USART_PIN     PIND
#define USART_RXD_PIN PIND0

#endif /* _TRANSCEIVER_H_ */

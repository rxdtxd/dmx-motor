// usart.h
// receive dmx data

#ifndef _USART_H_
#define _USART_H_

#include <inttypes.h>
#include "dmx.h"

// init usart for modbus transmit
void usart_init_modbus (void);

// init usart for dmx receive
void usart_init_dmx (void);

// disable usart
void usart_stop (void);

// transmit one data byte
void usart_transmit (uint8_t);

#endif /* _USART_H_ */

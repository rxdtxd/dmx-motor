// dmx->modbus transceiver

#include "transceiver.h"

#include <inttypes.h>
#include <avr/io.h>
#include <avr/wdt.h>      // TODO: disable with fuses and remove refs
//#include <util/delay.h>  // TODO: use or remove
#include <avr/interrupt.h>

#include "iocontrol.h"
#include "fakedelay.h"  // TODO: remove?
#include "metaboard.h"  // TODO: remove

#include "usart.h"
#include "dmx.h"
#include "crc.h"
#include "modbus.h"

dmx_t dmx = {IDLE, 1, 0, 0, 0, 0, 0, 255};


int main (void) {
    uint8_t c;        // cycle counter
    uint8_t chanval;  // only var for dmx channel
    //uint8_t retval;

    uint8_t modbus_data[8]; // data to send through modbus
    uint16_t tmp;

    wdt_disable();

    dmx.address = 1;
    chanval = 0;

    // leds are outputs
    leds_init();

    // led blink: devboard ok
    ledon(0); ledon(1); ledon(2);
    delay_ms(500);
    ledoff(0); ledoff(1); ledoff(2);

    usart_init_dmx();
    sei();

    // put data on usart/modbus if data on usart/dmx changed
    while (1) {
	//if (chanval != dmx.chanval[0]) {
	    ledon(1);     // debug: usart/modbus started
	    usart_stop();
	    usart_init_modbus();

	    chanval = dmx.chanval[0];

	    if (chanval == 0) {
		ledtoggle(2);

		// send STOP
		fill_cmd_stop(modbus_data);
		delay_ms(10);  // modbus start condition
		for (c = 0; c < 8; c++) {
		    usart_transmit(modbus_data[c]);
		}
		delay_ms(10);
	    } else {
		// calc frequency (255*24 = 6120)
		tmp = 24 * chanval;
		fill_cmd_freq(modbus_data, tmp);
		delay_ms(10);  // modbus start condition
		for (c = 0; c < 8; c++) {
		    usart_transmit(modbus_data[c]);
		}
		delay_ms(10);  // modbus stop condition

		// send RUN
		fill_cmd_run(modbus_data);
		delay_ms(10);  // modbus start condition
		for (c = 0; c < 8; c++) {
		    usart_transmit(modbus_data[c]);
		}
		delay_ms(10);
	    }

	    usart_stop();

	    usart_init_dmx();
	    ledoff(1);
	    delay_ms(500);
	    //} // if (chanval != dmx.chanval)
    }  // while (1)

    return 1;
}

// interrupt: usart receive complete
ISR (USART_RX_vect, ISR_BLOCK) {
    ledon(0);  // debug: int start

    // reading data clears status flags, so read status first
    dmx.status = UCSR0A;
    dmx.data = UDR0;

    // data overrun or frame error (break condition)
    if ( dmx.status & (_BV(DOR0)|_BV(FE0)) ) {
	dmx.state = BREAK;
    }
    else {
	switch (dmx.state) {  // previous slot's state
	case BREAK:
	    if (dmx.data != 0) dmx.state = IDLE;  // invalid start code
	    else {
		dmx.slot = dmx.address - 1;  // skip this many slots
		if (dmx.slot == 0) dmx.state = DATA; // dmx.address == 1
		else dmx.state = SKIP;
	    }
	    break;
	case SKIP:
	    if (--dmx.slot == 0) dmx.state = DATA;
	    break;
	case DATA:
	    if (dmx.chanval[dmx.slot] != dmx.data) {
		dmx.chanval[dmx.slot] = dmx.data;
		dmx.dataisnew |= ((uint16_t)1 << dmx.slot);
	    }
	    if (++dmx.slot == DMX_CHANNELS) dmx.state = IDLE;
	    break;
	case IDLE:
	    break;
	}
    }

    ledoff(0);  // debug: int stop
}

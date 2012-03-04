// modbus.c
// fill data array to be sent over modbus
// NOTE: implementation-specific hard-coded values, be vevy vevy keful!

#include "modbus.h"

#include <inttypes.h>
#include "crc.h"

void fill_cmd_run (unsigned char* data) {
    uint16_t crcdata;

    data[0] = (0x01);       // ADR 01h
    data[1] = (0x06);       // CMD 06h (write)
    data[2] = (0x20);       // MEM 20h
    data[3] = (0x00);       // MEM 00h
    data[4] = (0b00000000); // DAT hi  (not used)
    data[5] = (0b00000010); // DAT lo  (run)

    crcdata = crc(data, 6);
    data[6] = (uint8_t) (crcdata & 0x00ff); // CRC lo
    data[7] = (uint8_t) (crcdata>>8);       // CRC hi
}

void fill_cmd_stop (unsigned char* data) {
    uint16_t crcdata;

    data[0] = (0x01);       // ADR 01h
    data[1] = (0x06);       // CMD 06h (write)
    data[2] = (0x20);       // MEM 20h
    data[3] = (0x00);       // MEM 00h
    data[4] = (0b00000000); // DAT hi  (not used)
    data[5] = (0b00000001); // DAT lo  (stop)

    crcdata = crc(data, 6);
    data[6] = (uint8_t) (crcdata & 0x00ff); // CRC lo
    data[7] = (uint8_t) (crcdata>>8);       // CRC hi
}

void fill_cmd_freq (unsigned char* data, uint16_t freq) {
    uint16_t crcdata;

    data[0] = (0x01);       // ADR 01h
    data[1] = (0x06);       // CMD 06h (write)
    data[2] = (0x20);       // MEM 20h
    data[3] = (0x01);       // MEM 01h

    data[5] = (uint8_t) (freq & 0x00ff);  // DAT lo
    data[4] = (uint8_t) (freq>>8);        // DAT hi

    crcdata = crc(data, 6);
    data[6] = (uint8_t) (crcdata & 0x00ff); // CRC lo
    data[7] = (uint8_t) (crcdata>>8);       // CRC hi
}

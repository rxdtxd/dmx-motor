// modbus.h
// functions specific to vfd002l21b modbus protocol

#include <inttypes.h>

void fill_cmd_run (unsigned char* data);
void fill_cmd_stop (unsigned char* data);
void fill_cmd_freq (unsigned char* data, uint16_t freq);

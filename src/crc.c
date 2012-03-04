// CRC for Modbus RTU, ripped from VFD002L21B datasheet

unsigned int crc (unsigned char* data, unsigned int length) {
    int j;
    unsigned int reg_crc = 0xFFFF;
    while(length--){
	reg_crc ^= *data++;
	for(j=0; j<8; j++) {
	    if (reg_crc & 0x01) { /* LSB(b0)=1 */
		reg_crc = (reg_crc>>1) ^ 0xA001;
	    } else {
		reg_crc=reg_crc >>1;
	    }
	}
    }
    return reg_crc;
}

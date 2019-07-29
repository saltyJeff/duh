//
// Created by Jefferson on 6/14/2019.
//

#include "DuhSwitch.h"

DuhSwitch::DuhSwitch(const char *id,
		bool * const data,
		const byte len): DuhInput("SW", id), len(len), data(data) {
	zeroArray(data, len);
}
/*
 * Decoder functions
 */
byte nibble;
char nibbleToChar(byte nibble) {
	if(nibble <= 9) {
		return '0' + nibble;
	}
	else {
		return 'A' + nibble - 10;
	}
}

inline int maxIndex(int x, int s) {
	return ( (x) & ~( (s)-1) );
}


int i, endIndex; //i is array index, endindex is the ending index
void DuhSwitch::encodeData() {
	i = 0;
	endIndex = maxIndex(len, 4);
	for(; i < endIndex; i += 4) {
		nibble = 0;
		nibble |= data[i] << 3;
		nibble |= data[i+1] << 2;
		nibble |= data[i+2] << 1;
		nibble |= data[i+3] << 0;

		writeBuffer[writeIndex] = nibbleToChar(nibble);
		writeIndex++;
	}
	if(i < len) {
		nibble = 0;
		for(; i < len; i++) {
			nibble |= data[i] << (len - i);
		}
		writeBuffer[writeIndex] = nibbleToChar(nibble);
		writeIndex++;
	}
}
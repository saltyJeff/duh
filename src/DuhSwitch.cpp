//
// Created by Jefferson on 6/14/2019.
//

#include <cstring>
#include <cstdio>
#include "DuhSwitch.h"

char strEncodeBuffer[64];
bool readBuffer[48];

DuhSwitch::DuhSwitch(const char *id,
		bool * const data,
		const byte len): DuhInput("SW", id), len(len), data(data) {
	zeroArray(data, len);
}
char* DuhSwitch::poll() {
	bool diff = readInput();
	if(diff) {
		lastValid = millis();
		debounced = false;
	}
	else if(millis() - lastValid > DEBOUNCE_DELAY_MS && !debounced) {
		debounced = true;
		encodeInput(this);
		return strEncodeBuffer;
	}
	return nullptr;
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


int i, j, endIndex; //i is array index, j is string index
void encodeBuffer(const bool *data, const byte len, int start) {
	i = 0;
	j = start;
	endIndex = maxIndex(len, 4);
	for(; i < endIndex; i += 4) {
		nibble = 0;
		nibble |= data[i] << 3;
		nibble |= data[i+1] << 2;
		nibble |= data[i+2] << 1;
		nibble |= data[i+3] << 0;

		strEncodeBuffer[j] = nibbleToChar(nibble);
		j++;
	}
	if(i < len) {
		nibble = 0;
		for(; i < len; i++) {
			nibble |= data[i] << len - i;
		}
		strEncodeBuffer[j] = nibbleToChar(nibble);
		j++;
	}
	strEncodeBuffer[j] = 0;
}
void encodeInput(DuhSwitch* input) {
	strncpy(strEncodeBuffer, input->prefix, 2);
	strEncodeBuffer[2] = '-';
	strncpy(strEncodeBuffer+3, input->id, 3);
	strEncodeBuffer[6] = ':';
	encodeBuffer(input->data, input->len, 7);
	sprintf(strEncodeBuffer + j, "/%lx;", (input->lastValid) / 1000);
}
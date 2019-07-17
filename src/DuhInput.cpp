//
// Created by Jefferson on 7/16/2019.
//
#include "DuhInput.h"

byte writeIndex = 0;
char writeBuffer[32];
void DuhInput::serialize() {
	strncpy(writeBuffer, prefix, 2);
	writeBuffer[2] = '-';
	strncpy(writeBuffer+3, id, 3);
	writeBuffer[6] = ':';
	writeIndex = 7;
	encodeData();
	sprintf(writeBuffer + writeIndex, "/%02X;", checksum(writeBuffer, writeIndex));
}
byte checksum(const char *arr, const byte len) {
	byte c = 0;
	for(byte i = 0; i < len; i++) {
		c ^= arr[i];
	}
	return c;
}

byte readIndex = 0;
char readBuffer[32];
DuhInputData cachedInput;

bool tryFillCache();
bool readDuh(char c) {
	readBuffer[readIndex++] = c;
	readIndex = readIndex % 32;
	if(c == ';') {
		readIndex = 0;
		return tryFillCache();
	}
	return false;
}
// finite state machine states for the reading
char *currentField;
byte maxLen = 2;
byte cacheFieldIndex;
byte checksumIndex;
bool tryFillCache() {
	byte i = cacheFieldIndex = 0;
	currentField = cachedInput.prefix;
	maxLen = 2;
	cachedInput.hasChecksum = false;

	while(readBuffer[i] != ';') {
		byte c = readBuffer[i];
		switch(c) {
			//handle special chars first
			case '-':
				currentField = cachedInput.id;
				maxLen = 3;
				cacheFieldIndex = 0;
				break;
			case ':':
				currentField = cachedInput.data;
				maxLen = 32; //this isnt the proper value but an overestimate
				cacheFieldIndex = 0;
				break;
			case '/':
				currentField = cachedInput.checksum;
				maxLen = 2;
				cacheFieldIndex = 0;
				cachedInput.hasChecksum = true;
				checksumIndex = i;
				break;
			default:
				if(cacheFieldIndex > maxLen) {
					return false;
				}
				currentField[cacheFieldIndex++] = c;
		}
		i++;
	}
	if(cachedInput.hasChecksum) {
		// parse the checksum value from the checksum field
		byte challenge = (cachedInput.checksum[0] >= 'A' ? cachedInput.checksum[0] - 'A' + 10 : cachedInput.checksum[0] - '0') << 4; //absolutely disgusting
		challenge += cachedInput.checksum[1] >= 'A' ? cachedInput.checksum[1] - 'A' + 10 : cachedInput.checksum[1] - '0'; //positively filthy
		byte sum = checksum(readBuffer, checksumIndex);
		return sum == challenge;
	}
	else {
		return true;
	}
}
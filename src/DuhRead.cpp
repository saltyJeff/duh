//
// Created by Jefferson on 7/18/2019.
//

#include "DuhRead.h"
#include "checksum.h"

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
				maxLen = sizeof(cachedInput.id) - 1;
				cacheFieldIndex = 0;
				break;
			case ':':
				currentField = cachedInput.data;
				maxLen = sizeof(cachedInput.data) - 1; //this isnt the proper value but an overestimate
				cacheFieldIndex = 0;
				break;
			case '/':
				currentField = cachedInput.checksum;
				maxLen = sizeof(cachedInput.checksum) - 1;
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
		uint16_t challenge = strtol(cachedInput.checksum, NULL, 16);
		if(challenge == 0 && errno != 0) {
			return false;
		}
		uint16_t sum = checksum(readBuffer, checksumIndex);
		return sum == challenge;
	}
	else {
		return true;
	}
}
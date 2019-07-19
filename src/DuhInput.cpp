//
// Created by Jefferson on 7/16/2019.
//
#include "DuhInput.h"
#include "checksum.h"

byte writeIndex = 0;
char writeBuffer[32];
void DuhInput::serialize() {
	strncpy(writeBuffer, prefix, 2);
	writeBuffer[2] = '-';
	strncpy(writeBuffer+3, id, 3);
	writeBuffer[6] = ':';
	writeIndex = 7;
	encodeData();
	sprintf(writeBuffer + writeIndex, "/%04X;", checksum(writeBuffer, writeIndex));
}
//
// Created by Jefferson on 7/16/2019.
//
#include "DuhInput.h"
#include "checksum.h"

byte writeIndex = 0;
char writeBuffer[32];
void DuhInput::serialize() {
	sprintf(writeBuffer, "%.2s-%.3s:", prefix, id);
	writeIndex = 7;
	encodeData();
	sprintf(writeBuffer + writeIndex, "/%04X;", checksum(writeBuffer, writeIndex));
}
void requestInput(char *reqId, char *prefix, char *inputId) {
	sprintf(writeBuffer, "RQ-%.3s:%.2s-%.3s", reqId, prefix, inputId);
	sprintf(writeBuffer + 13, "/%04X;", checksum(writeBuffer, 13));
}
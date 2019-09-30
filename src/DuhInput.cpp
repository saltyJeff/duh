//
// Created by Jefferson on 7/16/2019.
//
#include "DuhInput.h"
#include "checksum.h"

char writeBuffer[MAX_MESSAGE_SIZE + 1] = "";
void DuhInput::serialize() {
	char *data = encodeData();
	byte checksumLen = sprintf(writeBuffer, PACKET_NO_CHECKSUM, prefix, id, data);
	sprintf(writeBuffer + checksumLen, "/%04X;", checksum(writeBuffer, checksumLen));
}
#ifdef RPC_SUPPORT
void requestInput(char *reqId, char *prefix, char *inputId) {
	sprintf(writeBuffer, "RQ-%.3s:%.2s-%.3s", reqId, prefix, inputId);
	sprintf(writeBuffer + 13, "/%04X;", checksum(writeBuffer, 13));
}
#endif
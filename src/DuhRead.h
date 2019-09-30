//
// Created by Jefferson on 7/18/2019.
//

#ifndef DUH_DUHREAD_H
#define DUH_DUHREAD_H

#include "../compat/compat.h"
#include "checksum.h"
#include "consts.h"

// read stuff
extern char readBuffer[MAX_MESSAGE_SIZE + 1];

struct DuhInputCache {
public:
	//char lengths are 1+ the minimum to hold the null byte
	char prefix[MAX_PREFIX_LEN + 1] = "";
	char id[MAX_ID_LEN + 1] = "";
	char data[MAX_DATA_LEN + 1] = "";
	char checksum[CHECKSUM_LENGTH + 1] = "";

	bool hasChecksum = false;
};

extern DuhInputCache input;
byte readDuh(char c);

const byte SEND_NOTHING = 0;
const byte SEND_ACK = 1;
const byte SEND_NAK = 2;
const byte WARNING_DISCARDED = 3;

#endif //DUH_DUHREAD_H

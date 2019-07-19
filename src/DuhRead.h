//
// Created by Jefferson on 7/18/2019.
//

#ifndef DUH_DUHREAD_H
#define DUH_DUHREAD_H

#include "../compat/compat.h"

// read stuff
extern char readBuffer[32];

//char lengths are 1+ the minimum to hold the null byte
struct DuhInputData {
public:
	char prefix[3] = "";
	char id[4] = "";
	char data[32] = "";
	char checksum[5] = "";
	bool hasChecksum;
};
extern DuhInputData cachedInput;
extern byte readIndex;
bool readDuh(char c);

#endif //DUH_DUHREAD_H

//
// Created by Jefferson on 7/18/2019.
//

#ifndef DUH_CHECKSUM_H
#define DUH_CHECKSUM_H
#include "../compat/compat.h"

const byte CHECKSUM_LENGTH = 4;
uint16_t checksum(const char *arr, const byte len);

#endif //DUH_CHECKSUM_H

//
// Created by Jefferson on 9/29/2019.
//
#include "../compat/compat.h"
#include "checksum.h"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define MAX_PREFIX_LEN 2
#define MAX_ID_LEN 3
#define MAX_DATA_LEN 15
//prefix + '-' + id + ':' + data + '/' + checksum + ';'
#define MAX_MESSAGE_SIZE MAX_PREFIX_LEN + 1 + MAX_ID_LEN + 1 + MAX_DATA_LEN + 1 + CHECKSUM_LENGTH + 1
#define PACKET_NO_CHECKSUM "%." STR(MAX_PREFIX_LEN) "s-%." STR(MAX_ID_LEN) "s:%." STR(MAX_DATA_LEN) "s"
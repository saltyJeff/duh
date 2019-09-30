//
// Created by Jefferson on 9/29/2019.
//

#ifndef DUH_STREQ_H
#define DUH_STREQ_H
#include <cstring>

inline bool streq(char *s1, char *s2) {
	return !strcmp(s1, s2);
}

#endif //DUH_STREQ_H

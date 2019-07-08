//
// Created by Jefferson on 6/14/2019.
//

#ifndef DUH_DUHINPUT_H
#define DUH_DUHINPUT_H

#include "../compat/compat.h"
#include <cstdio>

#ifndef INPUT_COUNT
#define INPUT_COUNT 5
#endif

class DuhInput {
public:
	const char *prefix;
	const char *id;
	DuhInput(const char *prefix, const char *id): prefix(prefix), id(id) {

	};

	virtual char* poll() = 0;
};

#endif //DUH_DUHINPUT_H

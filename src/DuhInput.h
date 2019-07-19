//
// Created by Jefferson on 6/14/2019.
//

#ifndef DUH_DUHINPUT_H
#define DUH_DUHINPUT_H

#include "../compat/compat.h"

#ifndef INPUT_COUNT
#define INPUT_COUNT 5
#endif

extern byte writeIndex;
extern char writeBuffer[32];
class DuhInput {
public:
	const char *prefix;
	const char *id;
	virtual ~DuhInput() = default;
	DuhInput(const char *prefix, const char *id): prefix(prefix), id(id) {};

	virtual bool poll() = 0;
	virtual void encodeData() = 0;
	void serialize();
};

#endif //DUH_DUHINPUT_H

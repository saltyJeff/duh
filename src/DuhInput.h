//
// Created by Jefferson on 6/14/2019.
//

#ifndef DUH_DUHINPUT_H
#define DUH_DUHINPUT_H

#include "../compat/compat.h"
#include "consts.h"

#ifndef INPUT_COUNT
#define INPUT_COUNT 5
#endif

extern char writeBuffer[MAX_MESSAGE_SIZE + 1];
class DuhInput {
public:
	const char *prefix;
	const char *id;
	virtual ~DuhInput() = default;
	DuhInput(const char *prefix, const char *id): prefix(prefix), id(id) {};

	virtual bool dirty() = 0;
	virtual char *encodeData() = 0;
	void serialize();
};
#ifdef RPC_SUPPORT
void requestInput(char *reqId, char *prefix, char *inputId);
#endif
#endif //DUH_DUHINPUT_H

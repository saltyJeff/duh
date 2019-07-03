//
// Created by Jefferson on 6/14/2019.
//

#ifndef DUH_DUHINPUT_H
#define DUH_DUHINPUT_H

#include "../compat/compat.h"

#ifndef INPUT_COUNT
#define INPUT_COUNT 5
#endif

extern char strEncodeBuffer[64];
extern bool readBuffer[48];
class DuhInput {
public:
	const char *prefix;
	const char *id;
	bool debounced = false;
	const byte len;
	unsigned long lastValid = 0;
	bool * const data;
	DuhInput(const char *prefix, const char *id, bool * const data, const byte len);

	virtual bool readInput() = 0;
	bool poll();
};
void encodeBuffer(const bool *data, const byte len, int start = 0);
void encodeInput(DuhInput *input);
inline void zeroArray(bool *data, byte len) {
	for(int i = 0; i < len; i++) {
		data[i] = 0;
	}
}

#endif //DUH_DUHINPUT_H

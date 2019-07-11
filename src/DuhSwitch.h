//
// Created by Jefferson on 6/14/2019.
//

#ifndef DUH_DUHSWITCH_H
#define DUH_DUHSWITCH_H

#include "../compat/compat.h"
#include "DuhInput.h"
#ifndef INPUT_COUNT
#define INPUT_COUNT 5
#endif

extern char strEncodeBuffer[64];
extern bool readBuffer[48];
const int DEBOUNCE_DELAY_MS = 50;
class DuhSwitch: public virtual DuhInput {
public:
	bool debounced = false;
	const byte len;
	unsigned long lastValid = 0;
	bool * const data;
	DuhSwitch(const char *id, bool * const data, const byte len);

	virtual bool readInput() = 0;
	char * poll();
};
void encodeBuffer(const bool *data, const byte len, int start = 0);
void encodeInput(DuhSwitch *input);
inline void zeroArray(bool *data, byte len) {
	for(int i = 0; i < len; i++) {
		data[i] = 0;
	}
}

#endif //DUH_DUHSWITCH_H

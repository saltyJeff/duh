//
// Created by Jefferson on 6/14/2019.
//

#ifndef DUH_DUHSWITCH_H
#define DUH_DUHSWITCH_H

#include "../src/DuhInput.h"
#ifndef INPUT_COUNT
#define INPUT_COUNT 5
#endif

const int DEBOUNCE_DELAY_MS = 50;
class DuhSwitch: public virtual DuhInput {
public:
	bool debounced = false;
	const byte len;
	unsigned long lastValid = 0;
	bool * const data;
	DuhSwitch(const char *id, bool * const data, const byte len);

	void encodeData();
	virtual bool poll() = 0;
};
inline void zeroArray(bool *data, byte len) {
	for(int i = 0; i < len; i++) {
		data[i] = 0;
	}
}

#endif //DUH_DUHSWITCH_H

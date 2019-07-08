//
// Created by Jefferson on 6/15/2019.
//

#ifndef DUH_LOCALINPUT_H
#define DUH_LOCALINPUT_H

#include <cstdlib>
#include "../src/DuhSwitch.h"

class LocalSwitch: public DuhSwitch  {
public:
	bool dirty = false;
	LocalSwitch(const char *id, const byte len);
	virtual bool readInput();
	~LocalSwitch() {
		free(data);
	}
};


#endif //DUH_LOCALINPUT_H

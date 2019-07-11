//
// Created by Jefferson on 6/15/2019.
//

#ifndef DUH_LOCALSWITCH_H
#define DUH_LOCALSWITCH_H

#include <cstdlib>
#include "../src/DuhSwitch.h"
#include "LocalInput.h"

class LocalSwitch: public LocalInput, public DuhSwitch {
public:
	bool dirty = false;
	LocalSwitch(const char *id, const byte len, GuiManager *gui);
	bool readInput();
	~LocalSwitch() {
		free(data);
	}
	void paint(int index);
};


#endif //DUH_LOCALSWITCH_H

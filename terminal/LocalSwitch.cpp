//
// Created by Jefferson on 6/15/2019.
//

#include "LocalSwitch.h"
#include <iostream>
using namespace std;

LocalSwitch::LocalSwitch(const char *id, const byte len): DuhInput("SW", id,  (bool * const)calloc(len, sizeof(bool)), len) {
	// is that an inline calloc + cast? DAMN RIGHT IT IS
}
bool LocalSwitch::readInput() {
	if(dirty) {
		dirty = false;
		return true;
	}
	return false;
}
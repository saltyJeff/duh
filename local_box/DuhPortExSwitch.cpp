//
// Created by Jefferson on 7/29/2019.
//

#include "DuhPortExSwitch.h"

DuhPortExSwitch::DuhPortExSwitch(const char *id, const uint8_t addr): DuhInput("SW", id), io(addr) {
	for(int i = P0; i <= P7; i++) {
		io.pinMode(i, INPUT);
	}
}
bool DuhPortExSwitch::poll() {
	byte newData = io.digitalReadAll();
	if(newData != lastData) {
		lastChanged = millis();
	}
	else if(millis() - lastChanged >= 50) { //enforce debounce
		return true;
	}
	return false;
}
void DuhPortExSwitch::encodeData() {
	sprintf(writeBuffer + writeIndex, "%02X", lastData);
	writeIndex++;
}
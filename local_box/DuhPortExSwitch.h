//
// Created by Jefferson on 7/29/2019.
//

#ifndef DUH_DUHPORTEXSWITCH_H
#define DUH_DUHPORTEXSWITCH_H
#define PCF8574_LOW_MEMORY
#include "../platforms/arduino/pcf8574/PCF8574.h"
#include "../src/DuhInput.h"

class DuhPortExSwitch: DuhInput {
public:
	DuhPortExSwitch(const char * id, const uint8_t addr);
	virtual bool poll();
	virtual void encodeData();
private:
	PCF8574 io;
	byte lastData = 0xAB;
	uint32_t lastChanged = 0;
};


#endif //DUH_DUHPORTEXSWITCH_H

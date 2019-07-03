//
// Created by Jefferson on 6/14/2019.
//
#ifndef ARDUINO_COMPAT_H
#define ARDUINO_COMPAT_H

#ifdef DESKTOP
#include <stdint.h>
typedef uint8_t byte;
const int INPUT_PULLUP = -1;
inline void pinMode(int pin, int mode) {}
#include <chrono>
using namespace std::chrono;
inline unsigned long millis() {
	milliseconds ms = duration_cast< milliseconds >(
			system_clock::now().time_since_epoch()
	);
	return ms.count();
}
#include "SerialPort.h"
#else
#include <Arduino.h>
#endif

#endif

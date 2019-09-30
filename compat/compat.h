//
// Created by Jefferson on 6/14/2019.
//
#ifndef ARDUINO_COMPAT_H
#define ARDUINO_COMPAT_H

#ifdef DESKTOP
#include <stdint.h>
typedef uint8_t byte;
#include <chrono>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <cstdlib>
using namespace std::chrono;
inline unsigned long millis() {
	milliseconds ms = duration_cast< milliseconds >(
			system_clock::now().time_since_epoch()
	);
	return ms.count();
}
#else
#include <Arduino.h>
#include <errno.h>
#include <util/crc16.h>
#endif

#endif

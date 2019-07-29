//
// Created by Jefferson on 7/2/2019.
//

#ifndef DUH_SERIALPORT_H
#define DUH_SERIALPORT_H

#include <cstdint>
#include "../include/libserialport.h"

#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x02
#define SERIAL_7N1 0x04
#define SERIAL_8N1 0x06
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x0A
#define SERIAL_7N2 0x0C
#define SERIAL_8N2 0x0E
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x22
#define SERIAL_7E1 0x24
#define SERIAL_8E1 0x26
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x2A
#define SERIAL_7E2 0x2C
#define SERIAL_8E2 0x2E
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x32
#define SERIAL_7O1 0x34
#define SERIAL_8O1 0x36
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x3A
#define SERIAL_7O2 0x3C
#define SERIAL_8O2 0x3E
class SerialPort {
private:
	sp_port *port = nullptr;
	bool enabled = false;
public:
	SerialPort();
	void begin(unsigned long);
	//void begin(unsigned long baud, uint8_t config);
	void end();
	int available();
	int read();

	int write(uint8_t val);
	int write(char *str);
	int write(char *str, int len);

	inline operator bool() { return enabled; }
	~SerialPort();
};

extern SerialPort Serial;
#endif //DUH_SERIALPORT_H

//
// Created by Jefferson on 7/2/2019.
//

#include "SerialPort.h"
#include <cstdlib>
SerialPort::SerialPort() {};
void SerialPort::begin(unsigned long) {
	enabled = false;
	char *portName = getenv("SERIAL_PORT");
	if(portName == nullptr) {
		return;
	}
	sp_get_port_by_name(portName, &port);
	if(port == nullptr) {
		return;
	}
	int baudrate = 9600;
	char *baud = getenv("BAUD_RATE");
	if(baud != nullptr) {
		baudrate = std::atoi(baud);
	}
	sp_set_baudrate(port, baudrate);
	sp_set_bits(port, 8);
	sp_set_stopbits(port, 1);
	sp_set_parity(port, sp_parity::SP_PARITY_NONE);
	enabled = true;
}
int SerialPort::available() {
	return sp_input_waiting(port);
}
int SerialPort::read() {
	char c;
	sp_return ret = sp_blocking_read(port, &c, 1, 0);
	if(ret != sp_return::SP_OK) {
		return -1;
	}
	return c;
}
int SerialPort::write(char *str) {
	int i = 0;
	while(*(str + i) != '\0') {
		write(*(str + i));
		i++;
	}
	return i;
}
int SerialPort::write(uint8_t val) {
	sp_blocking_write(port, &val, 1, 0);
	return 1;
}
int SerialPort::write(char *str, int len) {
	int i = 0;
	while(*(str + i) != '\0' && i < len) {
		write(*(str + i));
		i++;
	}
	return i;
}
void SerialPort::end() {}
SerialPort::~SerialPort() {
	if(port != nullptr) {
		sp_free_port(port);
	}
}

SerialPort Serial;
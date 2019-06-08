#ifndef DUH_H
#define DUH_H

#ifdef LOCAL_DBG
#include <stdint.h>
#define INPUT_PULLUP -1
void pinMode(int pin, int mode);
#endif

#include "utils.h"

class DuhInput {
public:
    const char* prefix;
    const char* id;
    uint32_t timestamp;
};

const int SWITCH_DDR = 0b11000001;

void prepSwitch(DuhInput& duhInput, const char *id, uint8_t& ddr);
void prepButton(DuhInput& duhInput, const char *id, int pin);

bool readSwitch(DuhInput& duhInput, uint8_t& port, const int count);
bool readButton(DuhInput& duhInput, int pin, char& state);
#endif
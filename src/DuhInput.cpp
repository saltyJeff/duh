#include "DuhInput.h"

void prepSwitch(DuhInput& duhInput, const char *id, uint8_t& ddr) {
    duhInput.prefix = "SW";
    duhInput.id = id;
    ddr = SWITCH_DDR;
}
void prepButton(DuhInput& duhInput, const char *id, int pin) {
    duhInput.prefix = "PB";
    duhInput.id = id;
    pinMode(pin, INPUT_PULLUP);
}

bool readSwitch(DuhInput& duhInput, uint8_t& port, const int count) {

}
bool readButton(DuhInput& duhInput, int pin, char& state) {

}
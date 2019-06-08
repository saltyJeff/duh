#include "local_utils.h"
#include <cassert>
#include <cstring>
void testSuite() {
    cout << "TEST SUITE" << endl;
    DuhInput tmp;
    uint8_t x;
    prepSwitch(tmp, "xy", x);
    assert(!strcmp("SW", tmp.prefix) && "switch prefix not set correctly");
    assert(!strcmp("xy", tmp.id) && "switch id not set correctly");
    assert(SWITCH_DDR == x && "switch ddr not set correctly");

    prepButton(tmp, "ab", 4);
    assert(!strcmp("PB", tmp.prefix) && "push button prefix not set correctly");
    assert(!strcmp("ab", tmp.id) && "push button id not set correctly");
    cout << "TESTS COMPLETE" << endl;
}

void dumpSwitches() {
    cout << "SWITCHES:" << endl;
    cout << '[';
    for(int i = 0; i < MAX_SWITCHES; i++) {
        cout << switches[i];
        if(i < MAX_SWITCHES - 1) {
            cout << ' ';
        }
    }
    cout << ']' << endl;
}
void dumpSwitchStr() {
    cout << "SWITCH STR: " << switchStr << endl;
}
void dumpInput(DuhInput& duhInput) {
    cout << "INPUT: " << duhInput.prefix << '-' << duhInput.id << endl;
}
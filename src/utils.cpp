#include "utils.h"

#ifdef LOCAL_DBG
void pinMode(int pin, int mode) {}
#endif

char nibble = 0;
bool switches[32];
char switchStr[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

void populateSwitchStr() {
    nibble = 0;
    int j = 0;
    for(int i = 0; i < MAX_SWITCHES; i+=4) {
        nibble |= switches[i] << 3;
        nibble |= switches[i+1] << 2;
        nibble |= switches[i+2] << 1;
        nibble |= switches[i+3] << 0;

        if(nibble < 9) {
            switchStr[j] = '0' + nibble;
        }
        else {
            switchStr[j] = 'A' + nibble - 10;
        }

        j++;
        nibble = 0;
    }
}
void parseSwitchStr() {
    int j = 0;
    nibble = 0;
    for(int i = 0; i < SWITCH_STR_LEN; i++) {
        if(switchStr[i] >= 'A') {
            nibble = switchStr[i] - 'A' + 10;
        }
        else {
            nibble = switchStr[i] - '0';
        }
        switches[j] = nibble & 1 << 3;
        switches[j] = nibble & 1 << 2;
        switches[j] = nibble & 1 << 1;
        switches[j] = nibble & 1;

        j += 4;
    }
}
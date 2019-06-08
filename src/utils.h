#ifndef DUH_UTIL_H
#define DUH_UTIL_H

const int MAX_SWITCHES = 32;
const int SWITCH_STR_LEN = MAX_SWITCHES / 4;
extern bool switches[MAX_SWITCHES];
extern char switchStr[SWITCH_STR_LEN + 1];

void populateSwitchStr();
void parseSwitchStr();

#endif
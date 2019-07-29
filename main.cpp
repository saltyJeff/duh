//add the compat layer to not get fucked by the compiler
#include <iostream>

using namespace std;

#ifdef CLI
#ifdef DEBUG
#include "terminal/testHarness.h"
#endif
#include "terminal/LocalSwitch.h"
#include "terminal/GuiManager.h"
#include "include/libserialport.h"
#else
extern void setup();
extern void loop();
#endif

int main(int argc, char *argv[]) {
#ifdef CLI
#ifdef DEBUG
	test();
#endif
	GuiManager manager;
	manager.startGui();
	manager.newSwitch("potato", 4);
	manager.newSwitch("thermostat", 16);
	manager.newSwitch("eggs", 11);
	while(manager.running) {
		manager.pollGui();
	}
#else
	// arduino simulation
	setup();
	while(true) {
		loop();
	}
#endif
	return 0;
}
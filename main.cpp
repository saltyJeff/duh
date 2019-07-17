//add the compat layer to not get fucked by the compiler
#include <iostream>

using namespace std;

#ifdef DEBUG
#include "terminal/testHarness.h"
#endif

#include "terminal/LocalSwitch.h"
#include "terminal/GuiManager.h"
#include "include/libserialport.h"

int main(int argc, char *argv[]) {
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
	return 0;
}
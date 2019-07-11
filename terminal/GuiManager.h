//
// Created by Jefferson on 7/1/2019.
//

#ifndef DUH_GUIMANAGER_H
#define DUH_GUIMANAGER_H

#include "curses.h"
#include "LocalSwitch.h"
#include <vector>
#include "libserialport.h"

using namespace std;
class GuiManager {
private:
	vector<LocalInput*> inputs;
	static void draw_borders(WINDOW *win);
	bool enterDown;
public:
	void newSwitch(const char *id, byte len);
	void startGui();
	void pollGui();
	bool running = true;
	int nextRow = 2;
	int selInput = 0;
	int selCol = 0;
	bool enter();
	~GuiManager();
};

char* intToStr(int i);
#endif //DUH_GUIMANAGER_H

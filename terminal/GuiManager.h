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
	vector<pair<LocalSwitch*, WINDOW*>> inputs;
	int selInput = 0;
	int selCol = 0;
	int nextRow = 2;
	static void draw_borders(WINDOW *win);
	static pair<int, int> dimensions(DuhInput *input, int maxCols);
public:
	void newSwitch(char *id, const byte len);
	void startGui();
	void pollGui();
	bool running = true;
	~GuiManager();
};


#endif //DUH_GUIMANAGER_H

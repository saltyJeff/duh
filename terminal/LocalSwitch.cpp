//
// Created by Jefferson on 6/15/2019.
//

#include "LocalSwitch.h"
#include "GuiManager.h"
#include <iostream>
#include <cstring>

using namespace std;
inline int max(int x, int y) {
	return (x > y) ? x : y;
}
LocalSwitch::LocalSwitch(const char *id, const byte len, GuiManager *gui): LocalInput(gui),
	DuhSwitch(id,  (bool * const)calloc(len, sizeof(bool)), len),
	DuhInput("SW", id){
	// is that an inline calloc + cast? DAMN RIGHT IT IS
	int rows = 5;
	int cols = max(strlen(id)+5, len*6+6);
	win = newwin(rows, cols, gui->nextRow, 0);
	gui->nextRow += rows;
}
bool LocalSwitch::readInput() {
	if(dirty) {
		dirty = false;
		return true;
	}
	return false;
}
void LocalSwitch::paint(int index) {
	mvwprintw(win, 0, 0, "SW_");
	mvwprintw(win, 0, 3, id);
	int rowIdx = 3;
	bool isSelected = index == gui->selInput;
	if(isSelected) {
		if(gui->selCol >= len) {
			gui->selCol = len - 1;
		}
		// handle enter key
		if(gui->enter()) {
			data[gui->selCol] = !data[gui->selCol];
			dirty = true;
		}
	}
	for(int i = 0; i < len; i++) {
		if(isSelected && i == gui->selCol) {
			wattron(win, A_REVERSE);
		}

		mvwprintw(win, 3, rowIdx, "[ ");
		rowIdx += 2;
		if(data[i]) {
			mvwprintw(win, 3, rowIdx, "X");
		}
		else {
			mvwprintw(win, 3, rowIdx, " ");
		}

		rowIdx++;
		mvwprintw(win, 3, rowIdx, " ]");
		rowIdx += 3;

		wattroff(win, A_REVERSE);
		mvwprintw(win, 2, rowIdx - 4, intToStr(i));
	}
}
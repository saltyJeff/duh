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
inline int min(int x, int y) {
	return (x < y) ? x : y;
}
const double COLS_PER_SWITCH = 7;

LocalSwitch::LocalSwitch(const char *id, const byte len, GuiManager *gui): LocalInput(gui),
	DuhSwitch(id,  (bool * const)calloc(len, sizeof(bool)), len),
	DuhInput("SW", id) {
	// is that an inline calloc + cast? DAMN RIGHT IT IS
	layout();
}
bool LocalSwitch::poll() {
	if(dirty) {
		dirty = false;
		return true;
	}
	return false;
}
void LocalSwitch::layout() {
	int colsToHold = COLS_PER_SWITCH * len + 5;
	int rows = (int)((colsToHold + 0.0) / (gui->maxCols()) + 0.5);
	if(rows < 1) {
		rows = 1;
	}
	rows *= 5;
	int cols = min(colsToHold, gui->maxCols());
	if(win != nullptr) {
		wdelch(win);
	}
	win = newwin(rows, cols, gui->nextRow, 0);
	gui->nextRow += rows;
	cout << rows << " " << cols << endl;
}
void LocalSwitch::paint(int index) {
	mvwprintw(win, 0, 0, "SW_");
	mvwprintw(win, 0, 3, id);
	int rowIdx = 3;
	int col = 3;
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

		//newline detection
		if(rowIdx + 5 > gui->maxCols()) {
			col += 3;
			rowIdx = 3;
		}
		mvwprintw(win, col, rowIdx, "[ ");
		rowIdx += 2;
		if(data[i]) {
			mvwprintw(win, col, rowIdx, "X");
		}
		else {
			mvwprintw(win, col, rowIdx, " ");
		}

		rowIdx++;
		mvwprintw(win, col, rowIdx, " ]");
		rowIdx += 3;

		wattroff(win, A_REVERSE);
		mvwprintw(win, col - 1, rowIdx - 4, intToStr(i));
	}
}
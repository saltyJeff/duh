//
// Created by Jefferson on 7/1/2019.
//

#include <cstring>
#include <iostream>
#include "GuiManager.h"
#include "../compat/SerialPort.h"
inline int max(int x, int y) {
	return (x > y) ? x : y;
}
char str[6];
char* intToStr(int i) {
	sprintf(str, "%d", i);
	return str;
}
void GuiManager::startGui() {
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
}
void GuiManager::pollGui() {
	int input = getch();
	switch(input) {
		case KEY_EXIT:
		case KEY_F(4):
		case KEY_END:
			running = false;
			return;
		case 'a':
		case KEY_LEFT:
			selCol--;
			break;
		case 'd':
		case KEY_RIGHT:
			selCol++;
			break;
		case 'w':
		case KEY_UP:
			selInput--;
			break;
		case 's':
		case KEY_DOWN:
			selInput++;
			break;
		case 10: //normal enter
		case ' ': {
			LocalSwitch *selected = inputs[selInput].first;
			selected->data[selCol] = !selected->data[selCol];
			selected->dirty = true;
			break;
		}
		case ERR:
		default:
			break;
	}
	// sanatize selInput and selRow
	if(selInput < 0) {
		selInput = 0;
	}
	if(selCol < 0) {
		selCol = 0;
	}
	if(selInput >= inputs.size()) {
		selInput = inputs.size() - 1;
	}
	if(selCol >= inputs[selInput].first->len) {
		selCol = inputs[selInput].first->len - 1;
	}
	for(int i = 0; i < inputs.size(); i++) {
		pair<DuhInput*, WINDOW*> pair = inputs[i];
		DuhInput *input = pair.first;
		WINDOW *win = pair.second;
		wclear(win);
		draw_borders(win);
		mvwprintw(win, 0, 0, "SW_");
		mvwprintw(win, 0, 3, input->id);
		int rowIdx = 3;
		for(int j = 0; j < input->len; j++) {
			if(i == selInput && j == selCol) {
				wattron(win, A_REVERSE);
			}

			mvwprintw(win, 3, rowIdx, "[ ");
			rowIdx += 2;
			if(input->data[j]) {
				mvwprintw(win, 3, rowIdx, "X");
			}
			else {
				mvwprintw(win, 3, rowIdx, " ");
			}

			rowIdx++;
			mvwprintw(win, 3, rowIdx, " ]");
			rowIdx += 3;

			wattroff(win, A_REVERSE);
			mvwprintw(win, 2, rowIdx - 4, intToStr(j));
		}

		if(input->poll()) {
			encodeInput(input);
			move(0, 0);
			clrtoeol();
			mvprintw(0, 0, strEncodeBuffer);
			printf(strEncodeBuffer);
			printf("\n");
			if(Serial) {
				Serial.write(strEncodeBuffer);
			}
		}
		wrefresh(win);
	}
}
void GuiManager::newSwitch(char *id, const byte len) {
	LocalSwitch *newInput = new LocalSwitch(id, len);
	pair<int, int> dims = dimensions(newInput, 80);
	WINDOW *newWin = newwin(dims.first, dims.second, nextRow, 0);
	nextRow += dims.first;
	inputs.push_back(pair<LocalSwitch*, WINDOW*>(newInput, newWin));
}
GuiManager::~GuiManager() {
	for(pair<DuhInput*, WINDOW*> pair : inputs) {
		DuhInput *input = pair.first;
		WINDOW *win = pair.second;

		free(input->data);
		delete input;
		wdelch(win);
	}
	endwin();
}
pair<int, int> GuiManager::dimensions(DuhInput *input, int maxCols) {
	//TODO: actually solve out
	int rows = 5;
	int cols = max(strlen(input->id)+5, input->len*6+6);
	return pair<int, int>(rows, cols);
}
void GuiManager::draw_borders(WINDOW *screen) {
	int x, y, i;
	getmaxyx(screen, y, x); // 4 corners
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y - 1, 0, "+");
	mvwprintw(screen, 0, x - 1, "+");
	mvwprintw(screen, y - 1, x - 1, "+");
	// sides
	for (i = 1; i < (y - 1); i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, x - 1, "|");
	}
	// top and bottom
	for (i = 1; i < (x - 1); i++) {
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y - 1, i, "-");
	}
}
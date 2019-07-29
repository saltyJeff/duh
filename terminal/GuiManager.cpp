//
// Created by Jefferson on 7/1/2019.
//

#include <cstring>
#include <iostream>
#include "GuiManager.h"
#include "../compat/SerialPort.h"

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
	needsRelayout();
	running = true;
}
void GuiManager::pollGui() {
	if(needsRelayout()) {
		nextRow = 2;
		for(LocalInput *input : inputs) {
			input->layout();
		}
	}
	int input = getch();
	bool enterPressedThisFrame = false;
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
			enterPressedThisFrame = true;
			enterDown = true;
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
	if(!enterPressedThisFrame) {
		enterDown = false;
	}
	for(int i = 0; i < inputs.size(); i++) {
		LocalInput *input = inputs[i];
		WINDOW *win = input->getWindow();
		wclear(win);
		draw_borders(win);
		input->paint(i);
		wrefresh(win);
		if(input->poll()) {
			input->serialize();
			move(0,0);
			clrtoeol();
			mvprintw(0, 0, writeBuffer);
			Serial.write(writeBuffer);
			printf("\n");
		}
	}
}
void GuiManager::newSwitch(const char *id, byte len) {
	LocalSwitch *newInput = new LocalSwitch(id, len, this);
	inputs.push_back(newInput);
}
GuiManager::~GuiManager() {
	for(LocalInput *input : inputs) {
		delete input;
	}
	endwin();
}
bool GuiManager::enter() {
	return enterDown;
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
bool GuiManager::needsRelayout() {
	int y, x;
	if(is_termresized() || (maxX == 0 && maxY == 0)) {
		resize_term(0,0);
		getmaxyx(stdscr, y, x);
		bool ret = false;
		if(y != maxY || x != maxX) {
			ret = true;
		}
		maxY = y;
		maxX = x;
		cout << "RESIZED" << endl;
		return ret;
	}
	return false;
}
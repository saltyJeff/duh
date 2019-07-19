//
// Created by Jefferson on 7/11/2019.
//

#ifndef DUH_LOCALINPUT_H
#define DUH_LOCALINPUT_H


#include "../src/DuhInput.h"
#include "curses.h"

class GuiManager;
class LocalInput: public virtual DuhInput {
public:
	GuiManager *gui;
	WINDOW *win = nullptr;
	explicit LocalInput(GuiManager *gui) {
		this->gui = gui;
	}
	virtual void paint(int index) = 0;
	virtual WINDOW *getWindow() {
		return win;
	}
	virtual void layout() = 0;
	virtual ~LocalInput() {
		if(win != nullptr) {
			wdelch(win);
		}
	};
};


#endif //DUH_LOCALINPUT_H

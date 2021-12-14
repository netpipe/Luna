/*
 * Mouse.h
 *
 *  Created on: 7 Dec 2021
 *      Author: ykhan
 */

#ifndef MOUSE_H_
#define MOUSE_H_

#include "InputDevice.h"

class Mouse;

using MousePtr = std::shared_ptr<Mouse>;

struct MouseState {
	long x;
	long y;
	bool btn1_pressed;
	bool btn2_pressed;
	bool btn3_pressed;
};

using MouseStatePtr = std::shared_ptr<MouseState>;

class Mouse: virtual public InputDevice {
public:
	enum Axis {
		x,
		y
	};

	virtual MouseStatePtr getMouseState() = 0;
};

#endif /* MOUSE_H_ */

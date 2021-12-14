/*
 * X11Mouse.h
 *
 *  Created on: 7 Dec 2021
 *      Author: ykhan
 */

#ifndef X11_X11MOUSE_H_
#define X11_X11MOUSE_H_

#include "X11InputController.h"
#include "X11InputDevice.h"
#include "../Mouse.h"

class X11Mouse;

using X11MousePtr = std::shared_ptr<X11Mouse>;

class X11Mouse: public X11InputDevice, public Mouse {
private:
	X11InputController* m_controller{nullptr};
public:
	X11Mouse(XIDeviceInfo* device_info, X11InputController* controller);
	virtual MouseStatePtr getMouseState();
};

#endif /* X11_X11MOUSE_H_ */

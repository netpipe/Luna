/*
 * X11Mouse.cpp
 *
 *  Created on: 7 Dec 2021
 *      Author: ykhan
 */

#include "X11Mouse.h"

X11Mouse::X11Mouse(XIDeviceInfo* device_info, X11InputController* controller)
	: X11InputDevice{device_info}, m_controller{controller} {
	// TODO Auto-generated constructor stub
	m_device_type = DeviceType::MOUSE;
}

MouseStatePtr X11Mouse::getMouseState() {
	MouseStatePtr mouse_state{nullptr};

	if (isMaster()) {
		return nullptr;
	}

	XDeviceState* device_state = m_controller->getXDeviceState(deviceId());

	if (!device_state) {
		printf("Failed to get X11 device state\n");
	}

	mouse_state = MouseStatePtr(new MouseState);
	XInputClass* cls;
	cls = device_state->data;

	for (int i = 0; i < device_state->num_classes; i++) {
		switch (cls->c_class) {
		case ValuatorClass:
		{
			auto val_state = (XValuatorState *) cls;

			if (val_state->num_valuators < 2) {
				printf("Error reading mouse state, valuators less than 2\n");
				return nullptr;
			}

			mouse_state->x = val_state->valuators[0];
			mouse_state->y = val_state->valuators[1];
            printf("pressure pen %i" ,val_state->valuators[2]);
			break;
		}
		case ButtonClass:
		{
			auto but_state = (XButtonState *) cls;
			mouse_state->btn1_pressed = but_state->buttons[0] & (1 << 1);
			mouse_state->btn2_pressed = but_state->buttons[0] & (1 << 2);
			mouse_state->btn3_pressed = but_state->buttons[0] & (1 << 3);
			/*
			for(int j = 1; j <= but_state->num_buttons; j++) {
				printf("\tbutton[%d]=%s\n", j,
						(but_state->buttons[j / 8] & (1 << (j % 8))) ? "down" : "up" );
			}
			*/
			break;
		}
		case KeyClass:
		{
			auto key_state = (XKeyState *) cls;
			break;
		}

		}
		cls = (XInputClass *) ((char *) cls + cls->length);
	}

//	MouseState state = m_controller->getMouseState();
	XFreeDeviceState(device_state);

	return mouse_state;
}

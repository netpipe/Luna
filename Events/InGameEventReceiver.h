#ifndef _IN_GAME_EVENTS_H
#define _IN_GAME_EVENTS_H 1
#include "../config.h"

#include <irrlicht.h>
#ifdef PHYSICS
#include "../Physics/Physics.h"
#include "../Physics/Vehicle.h"
#endif

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

	    enum
    {
        LEFT_MOUSE_BUTTON,
        MIDDLE_MOUSE_BUTTON,
        RIGHT_MOUSE_BUTTON,
        NUMBER_OF_MOUSE_BUTTONS
    };

class InGameEventReceiver : public IEventReceiver
{
 	// Public variables.
	public:
		bool Quit;

	// Private Variables
	private:
    bool keys[KEY_KEY_CODES_COUNT];

	// Public functions.
	public:



bool lmouse;

     bool mouseButtons[NUMBER_OF_MOUSE_BUTTONS];



    InGameEventReceiver();

	s32 mouseDeltaX;
	s32 mouseDeltaY;
	s32 mouseX;
	s32 mouseY;
	char * levent;
	s32 eid;

    void Init(void);

		virtual bool OnEvent ( const SEvent &event );

		bool getKeyState(EKEY_CODE key);


	// Private functions.
private:
//	SAppContext & Context;
};


#endif

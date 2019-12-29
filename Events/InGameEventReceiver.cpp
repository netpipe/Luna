#include "../config.h"
#ifdef EVENTS
#include "InGameEventReceiver.h"

InGameEventReceiver::InGameEventReceiver()
{
  for(s32 i = 0; i < KEY_KEY_CODES_COUNT; i++)
    keys[i] = false;
//    inputEventHappened =false;
	Quit = false;
}

bool InGameEventReceiver::OnEvent ( const SEvent &event )
{


		//let devloop know somehow to know when to run Lmain.py at all

  	if ( event.EventType == EET_GUI_EVENT )
	{
		s32 cid = event.GUIEvent.Caller->getID();

		switch ( event.GUIEvent.EventType )
		{
			case EGET_BUTTON_CLICKED:
				switch ( cid )
				{
					levent="button";
					eid=cid;
//					case 101:
//						quit = true;
						return true;
//					case 102:
//						login = true;
//						return true;
//
//					case 104:
//						conRefOK = true;
//						return true;
//
//					case 105:
//						wrongPassOK = true;
//						return true;
//
//					case 901:
//						devLogin = true;
//						return true;
				}
		}
	}
	  if(event.EventType == EET_KEY_INPUT_EVENT)
  {
    keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
  }
		if ( event.EventType == EET_MOUSE_INPUT_EVENT )
		{
//			if ( camera != NULL )
//				camera->OnEvent ( event );
			//printf("event on the mouse button");

			mouseX = event.MouseInput.X;
			mouseY = event.MouseInput.Y;
			mouseDeltaX = event.MouseInput.X - mouseX;
			mouseDeltaY = event.MouseInput.Y - mouseY;
			return true;
		}
	  return false;
}

bool InGameEventReceiver::getKeyState(EKEY_CODE key)
{
  return keys[key];
}
//bool InGameEventReceiver::getKeyState(EKEY_CODE key)
//{
//  return keys[key];
//}
#endif

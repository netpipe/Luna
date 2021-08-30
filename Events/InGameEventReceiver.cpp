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
			switch(event.MouseInput.Event)
            {
		case EMIE_LMOUSE_PRESSED_DOWN:
				printf("mousebutton left clicked");
                lmouse=true;
                mouseButtons[LEFT_MOUSE_BUTTON] = true;
                return true;

            case EMIE_RMOUSE_PRESSED_DOWN:
            printf("mousebutton rmouse clicked");
//            rmouse=true
                mouseButtons[RIGHT_MOUSE_BUTTON] = true;
                return true;

            case EMIE_MMOUSE_PRESSED_DOWN:
            printf("mousebutton mmouse clicked"); //use delay for python input system
                mouseButtons[MIDDLE_MOUSE_BUTTON] = true;
                return false;

            case EMIE_LMOUSE_LEFT_UP:
                mouseButtons[LEFT_MOUSE_BUTTON] = false;
              //  lmouse=false;
                return false;

            case EMIE_RMOUSE_LEFT_UP:
                mouseButtons[RIGHT_MOUSE_BUTTON] = false;
                return false;
//			case EMIE_MIDDLE_MOUSE_UP:
//                mouseButtons[RIGHT_MOUSE_BUTTON] = false;
//                return false;
//                MIDDLE_MOUSE_BUTTON

			default:

                break;
            }
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

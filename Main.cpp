#include "Luna.h"
#include <cstdio>

#ifdef __APPLE__
	#import <Cocoa/cocoa.h>

#include <OpenGL/OpenGL.h>
#include <Carbon/Carbon.h>
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFString.h>
#endif

#ifdef WIN32
	#include <winsock2.h>
#endif

//#ifdef __EMSCRIPTEN__
//#include <emscripten.h>
//#endif


////#ifdef WIN32
//#define COMPRESS
//#include "Input/Compress/mtar.h"
//////#include "Input/Compress/microtar/src/microtar-stdio.h"
//extern "C"{
//bool extractTar(char);
//
//}
//
//
////#endif // WIN64


int argc1=0;
 char** argv1;
bool init=1;

Luna game ( argc1,argv1 );

void main_loop(){

//switch (init){
//	case 1:{
//			init=false;
//		game.Run();
//		game.main_loop();
//    };break;
//    case 0:
//    {
            game.main_loop();
//    };break;
  //  }
}

int main ( int argc, char** argv )
{
	#ifdef __OSX__
		NSApplicationLoad();
	#endif

	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop,0,1);
#else
		Luna game ( argc,argv );
//#ifdef WIN32
//		  extractTar("../media/pydata.tar");
//#endif
		game.Run();
		while (!game.m_cInGameEvents.Quit){
			game.main_loop();
		}
		#endif // __EMSCRIPTEN__
		system("PAUSE");
	return 0;
}



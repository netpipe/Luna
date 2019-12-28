#include "Luna.h"
#include <cstdio>

#ifdef __APPLE__
	#import <Cocoa/cocoa.h>
#endif

#ifdef WIN32
	#include <winsock2.h>
#endif

//#ifdef __EMSCRIPTEN__
//#include <emscripten.h>
//#endif
int argc1=0;
 char** argv1;
bool init=1;

Luna game ( argc1,argv1 );
int result=1;

void main_loop(){
	while (result==1 ){
		if ( init ){
				init=false;

				game.Run();
				result = game.main_loop();
		}else{

				result = game.main_loop();
		}
	}
}


int main ( int argc, char** argv )
{
	#ifdef __OSX__
		NSApplicationLoad();
	#endif

	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop,0,1);
#else

		game.Run();

//		while (result==1 && !game.m_cInGameEvents.Quit){
		while (result==1 ){
		//		while (1){
			result = game.main_loop();
		}
		#endif // __EMSCRIPTEN__
		system("PAUSE");
	return 0;
}


#include "Luna.h"
#include <cstdio>

#ifdef __APPLE__
	#import <Cocoa/cocoa.h>
#endif

#ifdef WIN32
	#include <winsock2.h>
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
int argc1=0;
 char** argv1;

void main_loop(){
		Luna game ( argc1,argv1 );

		game.Run();

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

		game.Run();
		#endif // __EMSCRIPTEN__
		system("PAUSE");
	return 0;
}


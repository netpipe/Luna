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
bool init=true;
IrrlichtDevice *device;
        IVideoDriver *driver;
		ISceneManager *smgr;


#ifndef __EMSCRIPTEN__
void main_loop(){
	Luna game ( argc1,argv1 );
	while (!game.m_cInGameEvents.Quit){
		if ( init ){
				init=false;

				game.Run(device);
				//game.main_loop();
		}else{

				game.main_loop();
				//game.main_loop();
		}
	}
}
#endif

void main_loop2(){ //emscripten testing

		device->run();
		driver->beginScene ( true, true, SColor ( 31, 200, 111, 0 ) );
        smgr->drawAll();
		//guienv->drawAll();
        driver->endScene();
		device->sleep(15); // pythonize this

		}


int main ( int argc, char** argv )
{
	#ifdef __OSX__
		NSApplicationLoad();
	#endif


        #ifdef __EMSCRIPTEN__
       device = createDevice(video::EDT_OGLES2, core::dimension2du(800,600), 16, false, false, false);
#else
         device = createDevice(video::EDT_OPENGL, core::dimension2du(800,600), 16, false, false, false);

#endif
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
   // guienv = device->getGUIEnvironment();

	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop2,0,1);
#else
while (device->run())
main_loop();
		#endif // __EMSCRIPTEN__
		system("PAUSE");
	return 0;
}


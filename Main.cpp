//#define TESTINGEMSCRIPTEN also set in project options

#ifndef TESTINGEMSCRIPTEN
#include "Luna.h"


#else
    #include <unistd.h>

    #include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
#endif



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



#ifdef TESTINGEMSCRIPTEN
IrrlichtDevice *device;
        IVideoDriver *driver;
		ISceneManager *smgr;
#else
	Luna game ( argc1,argv1 );
#endif


//    void sleep(unsigned milliseconds)
//    {
//        usleep(milliseconds * 1000); // takes microseconds
//    }
#ifdef TESTINGEMSCRIPTEN
void main_loop2(){ //emscripten testing

		device->run();
		driver->beginScene ( true, true, SColor ( 31, 200, 111, 0 ) );
        smgr->drawAll();
		//guienv->drawAll();
        driver->endScene();
	//	device->sleep(15); // pythonize this
sleep(0.1);
//emscripten_sleep(1);

		}
		#endif

#ifndef TESTINGEMSCRIPTEN
#ifdef __EMSCRIPTEN__
void main_loop(){

//		while (1){
	while (!game.m_cInGameEvents.Quit){
		if ( init ){
				init=false;

				game.Run();
				game.main_loop2();
		}else{

				game.main_loop2();
				//game.main_loop();
		}
	}
}
#endif
#endif

int main ( int argc, char** argv )
{
	#ifdef __OSX__
		NSApplicationLoad();
	#endif

#ifdef TESTINGEMSCRIPTEN
			#ifdef __EMSCRIPTEN__
		   device = createDevice(video::EDT_OGLES2, core::dimension2du(800,600), 16, false, false, false);
	#else
			 device = createDevice(video::EDT_OPENGL, core::dimension2du(800,600), 16, false, false, false);

	#endif


		driver = device->getVideoDriver();
		smgr = device->getSceneManager();
	   // guienv = device->getGUIEnvironment();

//	   	IAnimatedMesh* mesh = smgr->getMesh("./media/sydney.md2");
//	if (!mesh)
//	{
//		device->drop();
//		return 1;
//	}
//	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
//
//		if (node)
//	{
//		node->setMaterialFlag(EMF_LIGHTING, false);
//		node->setMD2Animation(scene::EMAT_STAND);
//		node->setMaterialTexture( 0, driver->getTexture("./media/sydney.bmp") );
//	}


	   emscripten_set_main_loop(main_loop2,0,1);
	#endif

	#ifdef __EMSCRIPTEN__
	#ifndef TESTINGEMSCRIPTEN
		emscripten_set_main_loop(main_loop,0,1);
		#endif
	#else
			game.Run();
while (!game.m_cInGameEvents.Quit){
		//while (device->run()){

		game.main_loop();
		}
		#endif // __EMSCRIPTEN__
		system("PAUSE");
	return 0;
}


//! LUNA ENGINE 1.0
/// aha

//!TODO wondering how to get eeg and ai library into game for pattern recognition
// speech and directional forces
#include "Luna.h"
//
//Sound *Sound::m_sound = NULL;
//Sound Sound::m_default_sound_buffer;


#include <vector>
using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef ATMOSPHERE
#include "Scene/ATMOsphere.cpp"
#include "Scene/flares/CLensFlareSceneNode.h"
//#include "Scene/flares/LensFlareSceneNode.h"
#endif

#include "Scene/flares/SceneNodeAnimatorFollowCamera.h"
#include "GUI/compass/Compass.h"

#ifdef BOIDS
#include "Scene/boids/Flock.h"
#endif

#ifdef IRRc
#include "Net/IRRc/Application.h"
#endif

//#include "GUI/cImage2D.h"
#ifdef XEFFECTS
#include "Scene/XEffects/effectWrapper.h"
#endif

#ifdef PHYSICS
#include "./Input/Model/blender/IrrBlend.h"
#include "./Input/Model/blender/BulletBlendReader.h"
#include "./Input/Model/blender/blenderUp.h"
#endif

#include "./Equipment/firstPersonWeapon.h"

#ifdef ATMOSPHERE
#include "./TerrainFactory/CloudSceneNode/CCloudSceneNode.h"
#endif

#include "./Scene/decalManager/DecalManager.h"

//#include "GUI/CodeEditor/CGUIEditBoxIRB.h"
#include <fcntl.h> //needed for python

#ifdef COMPRESS
#include "./Input/Compress/Compress.h"
//Compress *archiver;
#include "./Input/Compress/zpipe.h"
#endif // COMPRESS

//#ifdef AgAudio
//	#include "./Input/AgAudio/Sound.h"
//#endif
//
//
//
//		#ifdef AgAudio
//		static Sound *m_sound;
//		static Sound m_default_sound_buffer;
//		#endif


#ifdef SDLSound
		#include "./Input/SDL/SDLsound.h"
#endif

#ifdef OPENAL2
	#include "./Input/openal_playback.h"
#endif

#ifdef SDLMixer // compile issues
		#include "./Input/SDLMixer.h"
#endif



//#define PostProcess

bool connected,doit,login=0;
// vector3df tmpvect;


//#define PYTHON
//#include <boost/python.hpp>   #not used just for ideas maybe
#include "Scripting/PythonManager.h"


#ifdef NDEBUG
#include <irrNet.h>

//    net::SOutPacket rotationPacket;
    net::INetManager* netManager;
	#include "Net/irrNetClient.h"



#ifdef RIBBONTRAIL
//#include "./Scene/RibbonTrailSceneNode/RibbonTrailSceneNode.h"
//       RibbonTrailSceneNode* rt;
#endif

//#include "TerrainFactory/GrassSceneNode/CWindGenerator.h"
//    scene::CGrassPatchSceneNode *grass[1000];
//scene::IWindGenerator *wind = createWindGenerator( 30.0f, 3.0f );
class ClientNetCallback : public net::INetCallback{
public:
	virtual void handlePacket(net::SInPacket& packet)
	{
	 //	u16 playerId = packet.getPlayerId();
	//	packet.decryptPacket("hushthisissecret");
	//	packet.deCompressPacket();
        printf("handleing the Packet\n");
			core::stringc str;
		packet >> str;

        if ( str == "first" ){  //great were connected
                std::cout << "we got handshake2" << str.c_str() << "\n"<< std::endl;
                connected=true;
                	//		    	packet2 << "actPack2";

        }
        if ( str == "second" ){  // this would be the login data
                std::cout << "hit second connected! \n" << str.c_str() << "\n"<< std::endl;
           //     connected=true;
                doit=true;
                	//		    	packet2 << "actPack2";
        }
        if ( str == "actPack2"){
               std::cout << "AUTHORIZED!!" << str.c_str() << "\n" << std::endl;
               login=true;
               connected=true;
//  if (!login){  // if has not logged in yet then send hands
        }else{
                std::cout << "other " << str.c_str() << "\n" << std::endl;
	}
        }
//        resetV=true;
        // m_cVehicle2->resetVehicle();//( core::vector3df(vec[0],vec[1],vec[2]));
      //  tmpvect=vector3df(vec);
 //     std::cout << str.c_str();
};
#endif
//ClientNetCallback* clientCallback;


int icount=0;

Luna::Luna ( int argc, char** argv ){}

Luna::~Luna(){}
//void main_loop();

int Luna::devloop(){
    #include "./DevLoop.h" //! DevLoop Entry
    return 0;
}

int Luna::mainloop(){
    #include "./MainLoop.h" //! MainLoop Entry
    return 0;
}

int Luna::doLogin ( const std::wstring &username, const std::wstring &password ){
    // 0 is ok, -1 logingood , 1 is no server connection
     #ifdef NDEBUG
     #ifdef NETWORK
    std::string uname ( username.begin(), username.end() );
    std::string pword ( password.begin(), password.end() );
    int iReturn;
    int authd=0;

while (!login){
    iReturn = -3;

    if(netManager->getConnectionStatus() != net::EICS_FAILED)
		{
        if (login==true){ iReturn= -1;};
			net::SOutPacket packet;
			if (connected==true)
            {  // check if already logged in send reset to server
                if (doit==true){ // send credentials if connected
                    packet << "userLogin";
                    printf("sending userLogin");
                    netManager->sendOutPacket(packet);
                }else{
                    printf ("not connected-connecting \n");
                    packet << "second";
                    netManager->sendOutPacket(packet);
                //    iReturn = -1; //
                }
            }
		        netManager->update(500);
				printf ("not connected-connecting \n");
    }
}
#endif
#endif
   return -1;//iReturn;//-1; //good for debugging
}

int Luna::handleMessages(){
	#ifdef NDEBUG
	#ifdef NETWORK
//     set some variables
		if (netManager->getConnectionStatus() != net::EICS_FAILED)
		{
        netManager->update(500);
		//	 packet.compressPacket();
		//	 packet.encryptPacket("hushthisissecret"); //16 char max
		}
		#endif
		#endif
return 0;
}

int Luna::shutdown(){

	#ifdef HUD
//	 delete CHUD2;
	#endif

    #ifdef BOIDS
	 //delete flock;
    #endif

    #ifdef PostProcess
    //if (bpostprocess){
	 delete ppBlurDOF;
	 delete ppBlur;
	// delete ppRenderer;
	// }
    #endif

	#ifdef ATMOSPHERE
    // delete atmo;
    #endif

	#ifdef ReflectiveWater
	/// delete water;
	#endif

	#ifdef RAGDOLL
		for (std::vector<RagDoll*>::iterator it = v_RagDolls.begin(); it != v_RagDolls.end(); ++it)
            (*it)->~RagDoll();
	#endif

	#ifdef COMPASS
	 delete Compass1;
	#endif

	#ifdef FLAG     // should be the flagmanager
//	if (bflagnode)
//		delete irrFlagNode;

	#endif

	#ifdef FLAG2     // should be the flagmanager
	 delete flag;
	#endif

	#ifdef PYTHON
		Py_Finalize();
    #endif

    #ifdef SOUND
		manager->releaseAllSources();
		manager->shutDown();
        cAudio::destroyAudioManager(manager);
    #endif

    #ifdef PHYSICS
		//clearBodies();
		//delete m_cVehicle;
	#endif

	#ifdef SPARK
		cout << "\nSPARK FACTORY BEFORE DESTRUCTION :" << endl;
		SPKFactory::getInstance().traceAll();
		SPKFactory::getInstance().destroyAll();
		cout << "\nSPARK FACTORY AFTER DESTRUCTION :" << endl;
		SPKFactory::getInstance().traceAll();
		device->drop();
	#endif

	#ifdef VIDEO
 //     delete vidmaster;
	 delete videoPlayer;
	#endif

	#ifdef NDEBUG
	 delete netManager;
    #endif

	//    delete ClientNetCallback;
	#ifdef PHYSICS
		delete m_cPhysics;
	// delete m_cScene;
	//delete m_cVehicle;

    #endif

    #ifdef AgAudio
    Sound::Instance()->Drop();
//        delete m_sound;

    #endif // AgAudio

	#ifdef FPS
		delete m_cPlayer;
	#endif

    guienv->drop();
    smgr->drop();
    device->drop();
    delete device;
    delete smgr;
    delete guienv;
    return 0;

}

int Luna::init(){
    bool FULLSCREEN=0;
    resolution[0]= 1024; resolution[1]= 768;
   //   resolution[0]= 2024; resolution[1]= 2768;

   if (FULLSCREEN){
    IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
    core::dimension2du res = nulldevice->getVideoModeList()->getDesktopResolution();
    nulldevice -> drop();
    #ifdef __EMSCRIPTEN__
			device = createDevice ( EDT_OGLES2,dimension2du (resolution[0],resolution[1]), 24, 1,1);
    #else
            device = createDevice ( EDT_OPENGL,dimension2du (resolution[0],resolution[1]), 24, 1,1);
    #endif
   }else {

      // device = createDevice ( EDT_OPENGL,dimension2du (res.Width,res.Height ),  32, true, true, false, 0 );
        #ifdef __EMSCRIPTEN__
			device = createDevice ( EDT_OGLES2,dimension2du (resolution[0],resolution[1]), 24, 0,1);
		#else
			device = createDevice ( EDT_OPENGL,dimension2du (resolution[0],resolution[1]), 24, 0,1);
		#endif
     //   device = createDevice ( EDT_SOFTWARE,dimension2du (resolution[0],resolution[1]), 24, 0,1);
// EDT_NULL       device = createDevice ( EDT_BURNINGSVIDEO,dimension2du (resolution[0],resolution[1]), 24, 0,1);

    };
    device->setWindowCaption ( L"Luna Engine v1-initial" );
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

//    	SAppContext context;
//	context.device = device;
//	context.counter = 0;
////	context.listbox = listbox;
//
//    		InGameEventReceiver m_cInGameEvents(context);


    device->setEventReceiver ( &m_cInGameEvents );
//Physics init
#ifdef PHYSICS
    m_cPhysics = new Physics();
    m_cPhysics->registerIrrDevice(device);
#endif

//networking
    #ifdef NDEBUG
    #ifdef NETWORK
        ClientNetCallback* clientCallback = new ClientNetCallback();
        netManager = net::createIrrNetClient(clientCallback, "127.0.0.1");
        netManager->setVerbose(true);           // debug messages
	#endif
    #endif


#ifdef AgAudio
//		Sound::Instance()->Create();
//	    Sound::Instance()->PlayBackgroundMusic(1);

//	m_sound->Create();
//	luna->m_sound->PlayBackgroundMusic(1);

#endif

#ifdef SDLMixer
//	SDLPlay();
#endif

#ifdef SDLSound
	sdlsoundinit();
#endif


#ifdef OPENAL2
	alplay();
#endif
    return 0;
}

int Luna::Run(){  // starts the game in dev mode or release mode some features are easier to impliment into the mainloop rather than scripting for testing //uses devloop or main_loop for emscripten




    events.devLogin=0;
    #ifndef NDEBUG
        events.devLogin=1;
    #endif
 //   driver->setVSync(0);
        	if ( events.devLogin && !this->m_cInGameEvents.Quit )  {
					//countr=countr+1;
					//printf("%i",countr);
					if (!iinit) {
							  if ( init() < 0 ) return -1;
                    device->setEventReceiver ( &m_cInGameEvents );
                    devloop();
		#ifdef PYTHON
			#ifdef __EMSCRIPTEN__
				TAR* tar;
				if (tar_open(&tar, "./media/pydata.tar", NULL, O_RDONLY, 0, 0) != 0) {
					fprintf(stderr, "Error: failed to open pydata.tar\n");
					exit(1);
				}
				if (tar_extract_all(tar, (char*) "/") != 0) {
					fprintf(stderr, "Error: failed to extract pydata.tar\n");
					exit(1);
				}
				tar_close(tar);

				//Py_Initialize(); //Initialize Python
			//	setenv("PYTHONHOME", "/media/", 0);
			#endif

		#ifdef EVENTS
			device->setEventReceiver ( &m_cInGameEvents );
		#endif

#ifdef __EMSCRIPTEN__

setenv("PYTHONHOME", "/", 0);
//			zstrdeflate("./media.zip");
    char *argv2[]={"appname", "media.zip" ,"testout","nulls"};
    int argc2= sizeof(argv2) / sizeof(char*) - 1;
//int test = zpipe(argc2,argv2);
#else
	//stringw workingDirectory = device->getFileSystem()->getWorkingDirectory();
	////workingDirectory+="media/lib/";
	//const  char* test = (const char*) workingDirectory.c_str();
	//
	//printf ( "working directory is %s " , test );
	//setenv("PYTHONHOME", (const char*)workingDirectory.c_str() , 0);
#endif

		Python::registerIrrDevice(this,*device,m_cInGameEvents);
		Py_Initialize();            //Initialize Python
		//PythonMultithreading goes here when time comes
		//    PyEval_InitThreads() ; // nb: creates and locks the GIL
		Python::init_irr();         //Initialize our module
		//Py_SetProgramName(), Py_SetPythonHome(), PyEval_InitThreads(), PyEval_ReleaseLock(), and PyEval_AcquireLock()
		//https://docs.python.org/2/c-api/init.html
		///todo check for empty or missing files or impliment the using command
		// Python::ExecuteScript("functions-list.pys"); // this is for testing

//    device->getFileSystem()->addFileArchive("./media/cards.zip");

		#ifdef __EMSCRIPTEN__
					Python::ExecuteScript("./media/functions-list.pys"); // this is for testing
								pyloader = "./media/main.pys";
			#else
				Python::ExecuteScript("../media/functions-list.pys"); // this is for testing
			#ifdef APPS

				pyloader = "./APP/cowsynth/main.pys";
				pyloader = "../media/main.pys";
			#else
				//pyloader = "./RACING/racer/main.pys";
				pyloader = "../media/main.pys";

			#endif

			//Python::PyIrr_LoadVehicle(m_cVehicle);
			//Python::PyIrr_addTerrain("1");
		#endif

		#ifdef EDITOR
			Python::bCodeEditor=3; // initial closed state
		#endif

	#endif //python
	} //init

				// run main devloop also EMSCRIPTEN loop
				#ifdef __EMSCRIPTEN__
					iinit=true;
					main_loop();
				#else
                    iinit=true;
                    main_loop();
                #endif
                }else{
                	//log into lobby if not in dev or debug mode.
//                	if (iinit){ shutdown(); exit(1); } // for exiting dev loop tmpfix
					printf ("now entering the lobby");
					if ( lobby() == -1 ) {
                        shutdown(); //exit
						//  break;
                        return 0;
                    } else {
                        printf("mainloop");
                        device->setEventReceiver ( &m_cInGameEvents );
                        mainloop();
                        //devloop();
                    }
            }
      //      getchar();
//      if (bshutdown==true) {
//		shutdown();
		//}



    return 1;
}

void Luna::main_loop(){ //devloop actually
//#ifdef __EMSCRIPTEN__
    //while (
//			emscripten_run_script("alert('hi')");

	#ifdef SDLMixer
	//sound_loop_then_quit();
	#endif

	#ifdef AgAudio
//	// Sound::Instance()->PlayAll();
	 // m_sound->Instance()->PlayAll();
	#endif

	device->run();
	//&& !this->m_cInGameEvents.Quit ) //&& !this->m_cInGameEvents.Quit
    // {
        const u32 now = device->getTimer()->getTime();
		frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		#ifdef PYTHON
        Python::PreRender();
        driver->beginScene ( true, true, SColor ( 0, 0, 0, 0 ) );
        Python::render();
		#else
		driver->beginScene ( true, true, SColor ( 31, 200, 111, 0 ) );
		#endif

        smgr->drawAll();
		//	device->setEventReceiver(&receiver);
		//device->sleep(5);

        #ifdef PostProcess
        if (Python::bPProcess ==1){
			ppBlurDOF->render( NULL );
            ppBlur->render( NULL );
        }
        #endif

	//       rt->render();
	#ifdef PYTHON
		#ifdef CODEEDITOR
		if (Python::bCodeEditor==1	){
			Python::bCodeEditor=0;
			windows->setVisible(true);
			codeEditor->setEnabled(true);
			codeEditor->setVisible(true);
			menu->setVisible(true);
			menu->setEnabled(true);
			windows->setVisible(true);
			device->setEventReceiver(&receiver);
			device->getCursorControl()->setVisible(true);
			    device->setResizable(true);
		}else if (Python::bCodeEditor == 3	){
			Python::bCodeEditor = 0;
			codeEditor->setEnabled(0);
			codeEditor->setVisible(false);
			menu->setVisible(false);
			menu->setEnabled(false);
			windows->setVisible(false);  //! not sure why but causes crashing on startup
		}
		#endif //code_editor
	//#endif
			//#ifdef PYTHON  //need this so endscene can be done before checkkeystates.
			Python::preEnd();
			Python::CheckKeyStates(); //located in pyInput can probably be moved to preEnd as its not being used to check keystates
			Python::ExecuteScript(irr::core::stringc(pyloader));
			//Python::ExecuteScript("./RACING/racer/main.pys");
			guienv->drawAll();
			driver->endScene();
		#else
			guienv->drawAll();
			driver->endScene();
		#endif

        int fps = driver->getFPS();
		if (lastFPS != fps)
		{
			core::stringw tmp(L"Luna Engine [");
			tmp += driver->getName();
			tmp += L"] fps: ";
			tmp += fps;
			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
		//sleep(0.101);
		usleep(100);
     //  device->sleep(5); // pythonize this
  //  }
//#endif
}

void Luna::CheckKeyStates(void){  //    obsolete:CheckKeyStates(); check onEvent for any need to check keys , used to be where python one sits now
}





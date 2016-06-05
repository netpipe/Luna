//! LUNA ENGINE 1.0
#include "Luna.h"

#include <vector>
using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#include "Scene/ATMOsphere.cpp"
#include "Scene/flares/CLensFlareSceneNode.h"
//#include "Scene/flares/LensFlareSceneNode.h"
#include "Scene/flares/SceneNodeAnimatorFollowCamera.h"
#include "GUI/compass/Compass.h"
#include "Scene/boids/Flock.h"
#include "Net/IRRc/Application.h"

#include "GUI/cImage2D.h"
#include "Scene/XEffects/effectWrapper.h"

#include "./FileSystem/Model/blender/IrrBlend.h"
#include "./FileSystem/Model/blender/BulletBlendReader.h"
#include "./FileSystem/Model/blender/blenderUp.h"

#include "./Equipment/firstPersonWeapon.h"
#include "./TerrainFactory/CloudSceneNode/CCloudSceneNode.h"
#include "./Scene/decalManager/DecalManager.h"

//#include <boost/python.hpp>   #not used just for ideas maybe

#define DPHYSICS
#define PYTHON
#include "Scripting/PythonManager.h"
#include <irrNet.h>
  //  net::SOutPacket rotationPacket;
    net::INetManager* netManager;
    bool connected,doit,login=0;
    vector3df tmpvect;

//#include "./Scene/RibbonTrailSceneNode/RibbonTrailSceneNode.h"
//       RibbonTrailSceneNode* rt;

//#include "TerrainFactory/GrassSceneNode/CWindGenerator.h"
//    scene::CGrassPatchSceneNode *grass[1000];
//scene::IWindGenerator *wind = createWindGenerator( 30.0f, 3.0f );

class ClientNetCallback : public net::INetCallback
{
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
                std::cout << "other " << str.c_str() << "\n" <<std::endl;
	}
        }
//        resetV=true;
        // m_cVehicle2->resetVehicle();//( core::vector3df(vec[0],vec[1],vec[2]));
      //  tmpvect=vector3df(vec);
 //     std::cout << str.c_str();
};
        ClientNetCallback* clientCallback;


int icount=0;

Luna::Luna ( int argc, char** argv ){}

Luna::~Luna(){}

int Luna::devloop(){
    #include "./DevLoop.h" //! DevLoop Entry
 //   system("PAUSE");
    return 0;
}

int Luna::mainloop(){
    #include "./MainLoop.h" //! MainLoop Entry
//    system("PAUSE");
    return 0;
}

int Luna::doLogin ( const std::wstring &username, const std::wstring &password ){
    // 0 is ok, -1 logingood , 1 is no server connection
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
   return -1;//iReturn;//-1; //good for debugging
}

int Luna::handleMessages(){
//     set some variables
		if (netManager->getConnectionStatus() != net::EICS_FAILED)
		{
        netManager->update(500);
//		//	 packet.compressPacket();
//		//	 packet.encryptPacket("hushthisissecret"); //16 char max
		}
return 0;
}

int Luna::shutdown(){
    delete netManager;
  //  delete ClientNetCallback;
    delete m_cPhysics;
//    delete m_cScene;
 //   delete m_cVehicle;
  //  delete m_cPlayer;
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
        device = createDevice ( EDT_OPENGL,dimension2du (resolution[0],resolution[1]), 24, 1,1);
   }else {
      // device = createDevice ( EDT_OPENGL,dimension2du (res.Width,res.Height ),  32, true, true, false, 0 );
        device = createDevice ( EDT_OPENGL,dimension2du (resolution[0],resolution[1]), 24, 0,1);
    };
    device->setWindowCaption ( L"Luna Engine v1-initial" );
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    device->setEventReceiver ( &m_cInGameEvents );
//Physics init
    m_cPhysics = new Physics();
    m_cPhysics->registerIrrDevice(device);
//networking
    #ifdef NDEBUG
        ClientNetCallback* clientCallback = new ClientNetCallback();
        netManager = net::createIrrNetClient(clientCallback, "127.0.0.1");
        netManager->setVerbose(true);           // debug messages
    #endif
    keyMap[0].Action = EKA_MOVE_FORWARD;    keyMap[0].KeyCode = KEY_KEY_W;
    keyMap[1].Action = EKA_MOVE_FORWARD;    keyMap[1].KeyCode = KEY_KEY_W;
    keyMap[2].Action = EKA_MOVE_BACKWARD;   keyMap[2].KeyCode = KEY_KEY_S;
    keyMap[3].Action = EKA_MOVE_BACKWARD;   keyMap[3].KeyCode = KEY_KEY_S;
    keyMap[4].Action = EKA_STRAFE_LEFT;     keyMap[4].KeyCode = KEY_KEY_A;
    keyMap[5].Action = EKA_STRAFE_LEFT;     keyMap[5].KeyCode = KEY_KEY_A;
    keyMap[6].Action = EKA_STRAFE_RIGHT;    keyMap[6].KeyCode = KEY_KEY_D;
    keyMap[7].Action = EKA_STRAFE_RIGHT;    keyMap[7].KeyCode = KEY_KEY_D;
    return 0;
}

int Luna::Run(){
    if ( init() < 0 ) return -1;
    events.devLogin=0;
    #ifndef NDEBUG
        events.devLogin=1;
    #endif
 //   driver->setVSync(0);
        	if ( events.devLogin )  {
                    device->setEventReceiver ( &m_cInGameEvents );
                    devloop();
                }else{
                printf ("now entering the lobby");
                   if ( lobby() == -1 ) {
                        shutdown(); //exit
                  //  break;
                        return 0;
                    } else {
                        printf("mainloop");
                        device->setEventReceiver ( &m_cInGameEvents );
                        mainloop();
                    }
            }
      //      getchar();
    shutdown();
    return 0;
}

void Luna::CheckKeyStates(void){}





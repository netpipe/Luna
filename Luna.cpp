//! LUNA ENGINE 1.0
/// aha

//!TODO wondering how to get eeg and ai library into game for pattern recognition
// speech and directional forces
#include "Luna.h"
//
//Sound *Sound::m_sound = NULL;
//Sound Sound::m_default_sound_buffer;
#include "config.h"

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
    #ifdef BULLETBLEND
        #include "./Input/Model/blender/IrrBlend.h"
        #include "./Input/Model/blender/BulletBlendReader.h"
        #include "./Input/Model/blender/blenderUp.h"
        #include "./Input/Model/blender/IrrBlendNew.h" //testing
    #endif
#endif

#ifdef IRRBULLET
//#include <irrBullet.h>
#include <irrBulletWorld.h>
#include <irrBulletRigidBody.h>
#include <irrBulletBoxShape.h>
#include <irrBulletSphereShape.h>
#include <irrBulletGImpactMeshShape.h>
#include <irrBulletRayCastVehicle.h>
#include <irrBulletCollisionObjectAffectorDelete.h>
#include <irrBulletCollisionObjectAffectorAttract.h>
#endif // IRRBULLET

#include "./Equipment/firstPersonWeapon.h"

#ifdef ATMOSPHERE
    #include "./TerrainFactory/CloudSceneNode/CCloudSceneNode.h"
#endif

    #include "./Scene/decalManager/DecalManager.h"



#include <fcntl.h> //needed for python

#ifdef COMPRESS
    #include "./Input/Compress/Compress.h"
    //Compress *archiver;
    #include "./Input/Compress/zpipe.h"
#endif // COMPRESS

#ifdef SDLSound
		#include "./Input/SDL/SDLsound.h"
		#include "./Input/SDL/SDL_fluidlite.h"
#endif

#ifdef OPENAL2
	#include "./Input/openal_playback.h"
#endif

#ifdef SDLMixer // compile issues
		#include "./Input/SDLMixer.h"
#endif

bool connected,doit,login=0;
// vector3df tmpvect;

//#define PYTHON
//#include <boost/python.hRpp>   #not used just for ideas maybe
#include "Scripting/PythonManager.h"


#ifdef RIBBONTRAIL
//#include "./Scene/RibbonTrailSceneNode/RibbonTrailSceneNode.h"
//       RibbonTrailSceneNode* rt;
#endif

//#include "TerrainFactory/GrassSceneNode/CWindGenerator.h"
//    scene::CGrassPatchSceneNode *grass[1000];
//scene::IWindGenerator *wind = createWindGenerator( 30.0f, 3.0f );


//#ifdef NDEBUG
#ifdef NETWORK
#include <irrNet.h>

//    net::SOutPacket rotationPacket;
    net::INetManager* netManager;
	#include "Net/irrNetClient.h"



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

ClientNetCallback* clientCallback;
#endif
//#endif



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
   //  #ifdef NDEBUG
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
//#endif
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
	// delete water;
	#endif

	#ifdef RAGDOLL
		for (std::vector<RagDoll*>::iterator it = v_RagDolls.begin(); it != v_RagDolls.end(); ++it)
            (*it)->~RagDoll();
	#endif

	#ifdef COMPASS
//	 delete Compass1;
	#endif

	#ifdef FLAG     // should be the flagmanager
//	if (bflagnode)
//		delete irrFlagNode;

	#endif

	#ifdef FLAG2     // should be the flagmanager
//	 delete flag;
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

 // just putting this here for testing irrbullet
//int addCube(const irr::core::vector3df &pos, const irr::core::vector3df &scale, irr::f32 mass, irr::core::stringc textureFile) const
//{
//    auto Node = device->getSceneManager()->addCubeSceneNode(1.0f);
//	Node->setScale(scale);
//	Node->setPosition(pos);
//	Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//	Node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
//	Node->setMaterialTexture(0, device->getVideoDriver()->getTexture(textureFile.c_str()));
//
//    Node->setMaterialFlag(irr::video::EMF_WIREFRAME, drawWireFrame);
//
//	auto shape = new IBoxShape(Node, mass, false);
//
//	auto body = world->addRigidBody(shape);
//
////	return body;
//}

//void shootCube(const irr::core::vector3df &scale, irr::f32 mass, irr::core::stringc textureFile) const
//{
//	irr::core::vector3df pos(camera->getPosition().X,camera->getPosition().Y,camera->getPosition().Z);
//
//	auto Node = device->getSceneManager()->addCubeSceneNode(1.0f);
//	Node->setScale(scale);
//	Node->setPosition(pos);
//	Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//	Node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
//	Node->setMaterialTexture(0, device->getVideoDriver()->getTexture(textureFile.c_str()));
//
//    Node->setMaterialFlag(irr::video::EMF_WIREFRAME, drawWireFrame);
//
//	auto shape = new IBoxShape(Node, mass, true);
//
//	auto body = world->addRigidBody(shape);
//
//	irr::core::vector3df rot = camera->getRotation();
//    irr::core::matrix4 mat;
//    mat.setRotationDegrees(rot);
//    irr::core::vector3df forwardDir(irr::core::vector3df(mat[8],mat[9],mat[10]) * 120);
//
//    body->setLinearVelocity(forwardDir);
//
//    body->setDamping(0.2,0.2);
//    body->setFriction(0.4f);
//
//    body->getAttributes()->addBool("collide", true);
//
//    return body;
//}
//
//void shootSphere(const irr::core::vector3df &scale, irr::f32 mass) const
//{
//	irr::core::vector3df pos(camera->getPosition().X,camera->getPosition().Y,camera->getPosition().Z);
//
//	auto Node = device->getSceneManager()->addSphereSceneNode();
//	Node->setScale(scale);
//	Node->setPosition(pos);
//	Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//	Node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
//	Node->setMaterialTexture(0, device->getVideoDriver()->getTexture("rockwall.jpg"));
//
//	if(drawWireFrame)
//        Node->setMaterialFlag(irr::video::EMF_WIREFRAME, drawWireFrame);
//
//	auto shape = new ISphereShape(Node, mass, true);
//
//	auto body = world->addRigidBody(shape);
//	body->setDamping(0.2,0.2);
//
//    // Since we use a "bumpy" triangle mesh for the terrain, we need to set the CCD radius and
//    // motion threshold to ensure that we don't have any tunneling problems.
//    // This doesn't work very well for box shapes.
//	// ALSO: If you use setLocalScaling() on the collision shape, be sure to call this again
//	// after scaling to make sure that it matches the actual object.
//
//	irr::core::vector3df rot = camera->getRotation();
//    irr::core::matrix4 mat;
//    mat.setRotationDegrees(rot);
//    irr::core::vector3df forwardDir(irr::core::vector3df(mat[8],mat[9],mat[10]) * 120);
//
//    body->setLinearVelocity(forwardDir);
//
//
//
//    //ICollisionObjectAffectorDelete *deleteAffector = new ICollisionObjectAffectorDelete(4000);
//    //body->addAffector(deleteAffector);
//
//    return body;
//}
//
//void createTank(const irr::core::stringw& file, const irr::core::stringw& collFile,
//    const irr::core::vector3df &pos, const irr::f32 mass) const
//{
//	auto Node = device->getSceneManager()->addAnimatedMeshSceneNode(
//        device->getSceneManager()->getMesh(file.c_str()));
//	Node->setPosition(pos);
//	Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//
//
//	auto shape = new IGImpactMeshShape(Node, device->getSceneManager()->getMesh(collFile.c_str()), mass);
//
//	auto tank = world->addRigidBody(shape);
//	tank->includeNodeOnRemoval(false);
//
//    tank->setName("Tank");
//	tank->getAttributes()->addBool("vehicle", true);
//	tank->getAttributes()->addBool("destroyable", true);
//	tank->getAttributes()->addBool("isDestroyed", false);
//
//    // When using a raycast vehicle, we don't want this rigid body to deactivate.
//	tank->setActivationState(EActivationState::EAS_DISABLE_DEACTIVATION);
//
//    // We create our vehicle, passing our newly created rigid body as a parameter.
//	auto vehicle = world->addRaycastVehicle(tank);
//
//
//    // Set up our wheel construction info. These values can be changed for each wheel,
//    // and the values that you want to keep will stay the same, that way
//    // all parameters for each wheel can stay the same for what needs to remain equal,
//    // such as directions and suspension rest length.
//    SWheelInfoConstructionInfo wheel;
//    wheel.chassisConnectionPointCS = irr::core::vector3df(0.0,-0.88,4.0);
//    wheel.wheelDirectionCS = irr::core::vector3df(0.0,-1,0.0);
//    wheel.wheelAxleCS = irr::core::vector3df(-2,0.0,0.0);
//    wheel.suspensionRestLength = 0.6;
//    wheel.wheelRadius = 8.0;
//    wheel.isFrontWheel = false;
//
//    wheel.chassisConnectionPointCS = irr::core::vector3df(-4, -0.6, 12);
//    vehicle->addWheel(wheel);
//
//    wheel.chassisConnectionPointCS = irr::core::vector3df(4, -0.6, 12);
//    vehicle->addWheel(wheel);
//
//    wheel.chassisConnectionPointCS = irr::core::vector3df(-4, -0.6, -12);
//    vehicle->addWheel(wheel);
//
//    wheel.chassisConnectionPointCS = irr::core::vector3df(4, -0.6, -12);
//    vehicle->addWheel(wheel);
//
//	for(irr::u32 i=0;i<vehicle->getNumWheels();i++)
//    {
//        SWheelInfo &info = vehicle->getWheelInfo(i);
//
//        info.suspensionStiffness = 0.15f;
//        info.wheelDampingRelaxation = 2.3f;
//        info.wheelDampingCompression = 4.4f;
//        info.frictionSlip = 1000; // Higher values keeps the aircraft from jittering when landing unevenly
//        info.rollInfluence = 0.1f; // Rolls easier at higher values
//
//
//        // We call updateWheel, which takes SWheelInfo as the first parameter,
//        // and the ID of the wheel to apply that info to. This must
//        // be called after any changes in order for the changes to actually take effect.
//        vehicle->updateWheelInfo(i);
//    }
//
//    // Set a reference to the raycast vehicle so that irrBullet will automatically remove it when the object is removed
//    tank->setVehicleReference(vehicle);
//
//    return tank;
//}


//
//irr::scene::IParticleSystemSceneNode* const createParticleSystem(const irr::core::vector3df& dir, irr::f32 min, irr::f32 max,
//    const irr::video::SColor& darkest, const irr::video::SColor& brightest, irr::f32 minAge, irr::f32 maxAge, irr::f32 angle,
//    const irr::core::dimension2df& minSize, const irr::core::dimension2df maxSize, const irr::core::stringc& textureFile,
//    irr::f32 lifeTime, bool gravity, irr::video::E_MATERIAL_TYPE materialType, bool fadeOut) const
//{
//	auto ps =
//    device->getSceneManager()->addParticleSystemSceneNode(false);
//
//    auto em = ps->createBoxEmitter(
//        irr::core::aabbox3d<irr::f32>(-7,0,-7,7,1,7), // emitter size
//        dir,   // initial direction core::vector3df(0.0f,0.01f,0.0f)
//        min,max,                             // emit rate
//        darkest,       // darkest color
//        brightest,       // brightest color
//        minAge,maxAge,angle,                         // min and max age, angle
//        minSize,         // min size
//        maxSize);        // max size
//
//    ps->setEmitter(em); // this grabs the emitter
//    em->drop(); // so we can drop it here without deleting it
//
//    if(fadeOut)
//    {
//        auto paf = ps->createFadeOutParticleAffector();
//        ps->addAffector(paf); // same goes for the affector
//        paf->drop();
//    }
//
//    if(gravity==true)
//    {
//        auto paf = ps->createGravityAffector(irr::core::vector3df(0.0f,-0.007f, 0.0f), 1800);
//        ps->addAffector(paf); // same goes for the affector
//        paf->drop();
//    }
//
//    ps->setScale(irr::core::vector3df(0.4,0.4,0.4));
//    ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//    ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
//    ps->setMaterialTexture(0, device->getVideoDriver()->getTexture(textureFile.c_str()));
//    ps->setMaterialType(materialType);
//
//    if(lifeTime > 0.0f)
//    {
//        irr::scene::ISceneNodeAnimator* anim = device->getSceneManager()->createDeleteAnimator(lifeTime);
//        ps->addAnimator(anim);
//        anim->drop();
//    }
//
//    return ps;
//}

//
//void createGround() const
//{
//    auto Node = device->getSceneManager()->addCubeSceneNode(1.0);
//	Node->setScale(irr::core::vector3df(600,3,600)); // 400, 3, 400
//	Node->setPosition(irr::core::vector3df(200,0,100));
//	Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//	Node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
//	Node->setMaterialTexture(0, device->getVideoDriver()->getTexture("rockwall.jpg"));
//
//    if(drawWireFrame)
//        Node->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
//
//	auto shape = new IBoxShape(Node, 0, false);
//
//	auto body = world->addRigidBody(shape);
//
//	return body;
//}


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
            #ifdef __linux__
			device = createDevice ( EDT_OPENGL,dimension2du (resolution[0],resolution[1]), 24, 0,1);
			#elif __APPLE__
			device = createDevice ( EDT_OPENGL,dimension2du (resolution[0],resolution[1]), 24, 0,1);
			#else //windows
			device = createDevice ( EDT_OPENGL,dimension2du (resolution[0],resolution[1]), 24, 0,1); // has issues with RDP had to rename windows/system32/atig6pxxx.dll to .dll.bak but causes opengl to not work system wide

			//device = createDevice ( EDT_SOFTWARE,dimension2du (resolution[0],resolution[1]), 24, 0,1); // for development and speed over RDP
			//device = createDevice ( EDT_BURNINGSVIDEO,dimension2du (resolution[0],resolution[1]), 24, 0,1);


			#endif
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

#ifdef IRRBULLET
    world = createIrrBulletWorld(device, true, 1); //

   // world->setDebugMode(EPDM_DrawAabb |     //       EPDM_DrawContactPoints);

    world->setGravity(vector3df(0,-10,0));


//        auto Node = device->getSceneManager()->addCubeSceneNode(1.0);
//	Node->setScale(irr::core::vector3df(600,3,600)); // 400, 3, 400
//	Node->setPosition(irr::core::vector3df(200,0,100));
//	Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//	Node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
//	Node->setMaterialTexture(0, device->getVideoDriver()->getTexture("rockwall.jpg"));
//
//    if(1)
//        Node->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
//
//	auto shape = new IBoxShape(Node, 0, false);
//
//	auto body = world->addRigidBody(shape);

//int columns=5;
//int rows = 5;
//    for(u32 j=0; j < columns; j++)
//    {
//        for(u32 i=0; i < rows; i++)
//        {
//           // addCube(vector3df(3*j, 0+3*i+3, 0), vector3df(3,3,3), 3);
//
//        auto Node = device->getSceneManager()->addCubeSceneNode(1.0f);
//	Node->setScale(vector3df(3,3,3));
//	Node->setPosition(vector3df(3*j, 0+3*i+3, 0));
//	Node->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//	Node->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
////	Node->setMaterialTexture(0, device->getVideoDriver()->getTexture(textureFile.c_str()));
//
//    Node->setMaterialFlag(irr::video::EMF_WIREFRAME, 1);
//
//	auto shape = new IBoxShape(Node, 10, false);
//
//	auto body = world->addRigidBody(shape);
//       }
//    }
   // camera = device->getSceneManager()->addCameraSceneNodeFPS();
	//camera->setPosition(vector3df(50,15,200));


//	createGround();
//	createBoxes();
	#endif

//networking
    #ifdef NDEBUG
    #ifdef NETWORK
        ClientNetCallback* clientCallback = new ClientNetCallback();
        netManager = net::createIrrNetClient(clientCallback, "127.0.0.1");
        netManager->setVerbose(true);           // debug messages
	#endif
    #endif

#ifdef SOUND2

manager = cAudio::createAudioManager(false);
	if(audioMgr)
	{
		cAudio::IAudioDeviceList* pDeviceList = cAudio::createAudioDeviceList();
		unsigned int deviceCount = pDeviceList->getDeviceCount();
		cAudio::cAudioString defaultDeviceName = pDeviceList->getDefaultDeviceName();
				for(unsigned int i=0; i<deviceCount; ++i)
		{
			cAudio::cAudioString deviceName = pDeviceList->getDeviceName(i);
			if(deviceName.compare(defaultDeviceName) == 0)
				cout << i << "): " << deviceName.c_str() << " [DEFAULT] \n";
			else
				cout << i << "): " << deviceName.c_str() << " \n";
		}
manager->initialize(pDeviceList->getDeviceName(1).c_str());
}
#endif
#ifdef AgAudio
		Sound::Instance()->Create();
	    Sound::Instance()->PlayBackgroundMusic(1);
#endif

#ifdef SDLMixer
//	SDLPlay();
#endif
#ifdef FLUIDLITE
//	initFluidLite();
#endif
#ifdef SDLSound1
	//sdlsoundinit();
#endif

#ifdef OPENAL2
	alplay();
#endif

#ifdef CODEEDITOR
    windows = guienv->addWindow(
            rect<s32>(100 , 100 , 800 , 800 ),
            false, // modal?
            L"Test window");
#endif

    return 0;
}



//#######################################################################################

int Luna::Run(){  // starts the game in dev mode or release mode some features are easier to impliment into the mainloop rather than scripting for testing //uses devloop or main_loop for emscripten

    events.devLogin=0;
    #ifndef NDEBUG2  // put 2 here to disable for now its used to login
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
            stringw workingDirectory = device->getFileSystem()->getWorkingDirectory();
           // workingDirectory+="../media/lib/";
            //const  char* test = (const char*) workingDirectory.c_str();
            //
            printf ( "working directory is %s " , workingDirectory.c_str() );

            //find a way to set the ../media/lib folder after untaring
            #ifdef __linux__
            //setenv("PYTHONHOME", (const char*)workingDirectory.c_str() , 0);

            #else
           // workingDirectory = "C:\Python27"
            //workingDirectory =
          // / Py_SetPythonHome("python");

  //        device->getFileSystem()->addFileArchive("..\\media\\pydata.zip");
// Py_SetPythonHome( "pydata" ); // needs fixing still
           Py_SetPythonHome( "..\\media\\pydata\\" ); // needs fixing still
            //PySys_SetPath( 'C:/Dev/Luna/media/pydata/lib/'
            #endif
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
				pyloader = "./media/gameloader.pys";
			#else
				Python::ExecuteScript("../media/functions-list.pys"); // this is for testing
                pyloader = "../media/main.pys";
			#endif
                pyloader = "../media/gameloader.pys";
                Python::ExecuteScript(pyloader);
                //Python::PyIrr_LoadVehicle(m_cVehicle);
                //Python::PyIrr_addTerrain("1");
                //	Luna::returnString="../media/gameloader.pys";
		#ifdef CODEEDITOR
			Python::bCodeEditor=3; // initial closed state
		#endif
	#endif //python
	} //init


	//#########################################################################################
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
                      //  mainloop();
                        main_loop();
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

	device->run();
	//&& !this->m_cInGameEvents.Quit ) //&& !this->m_cInGameEvents.Quit
    // {
        const u32 now = device->getTimer()->getTime();
		frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		#ifdef IRRBULLET3 //not needed
        world->stepSimulation(frameDeltaTime*0.001f, 120);
//        world->debugDrawWorld(debugDraw);
        // This call will draw the technical properties of the physics simulation
        // to the GUI environment.
        world->debugDrawProperties(true);
		#endif

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
            //if (Python::bPProcess ==1){
            //ppBlurDOF->render( NULL );
            //ppBlur->render( NULL ); }
        #endif

	//       rt->render();

	#ifdef PYTHON
		#ifdef CODEEDITOR
		if ( Python::bCodeEditor==1	){
			Python::bCodeEditor=0;
			windows->setVisible(true);
//			codeEditor->setEnabled(true);
//			codeEditor->setVisible(true);
//			menu->setVisible(true);
//			menu->setEnabled(true);
//			windows->setVisible(true);
////			device->setEventReceiver(&receiver);
//			device->getCursorControl()->setVisible(true);
//			    device->setResizable(true);
		}else if ( Python::bCodeEditor == 3	){
			Python::bCodeEditor = 0;
		//	codeEditor->setEnabled(0);
		//	codeEditor->setVisible(false);
		//	menu->setVisible(false);
		//	menu->setEnabled(false);
			windows->setVisible(false);  //! not sure why but causes crashing on startup
		}
		#endif //code_editor

			Python::preEnd();
			Python::CheckKeyStates(); //located in pyInput can probably be moved to preEnd as its not being used to check keystates
//CheckKeyStates();
			//Python::ExecuteScript(irr::core::stringc(Python::returnString));
			//Python::ExecuteScript(Python::returnString);
			Python::ExecuteScript(irr::core::stringc(pyloader));
		//	printf(Python::returnString.c_str());
		//	printf("\n");
		//	printf(pyloader);

			guienv->drawAll();
			driver->endScene();
		#else
			guienv->drawAll();
			driver->endScene();
		#endif //PYTHON

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

void Luna::CheckKeyStates(void){
 //    obsolete:CheckKeyStates();
 //check onEvent for any need to check keys ,
 // used to be where python one sits now
printf("check keys\n");

bool tester=true;
printf("%i booltest",tester);

                //Python::bPProcess=1;
                 printf("%i cks", m_cInGameEvents.mouseButtons[LEFT_MOUSE_BUTTON]);
                 printf("%i cks", m_cInGameEvents.lmouse);

                if (m_cInGameEvents.rmouse){
                 printf("123mouse clicked");
                 Python::rmouse1=m_cInGameEvents.rmouse;
                }
                 Python::lmouse1=m_cInGameEvents.lmouse;
                 Python::mmouse1=m_cInGameEvents.mmouse;
}





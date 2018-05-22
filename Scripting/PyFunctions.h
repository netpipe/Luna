///Main Python Function Includes
///Stuff Relivent to Initialization and management of scene / sound and managers.

#define DSOUND
#include "../Luna.h"
#include <cstdlib>
    #define MAX_DECALS 50
   // #define IRRCD   // irrlicht Collision Detection
    #define IRRc
 //   #define PostProcess
    #define ReflectiveWater
    #define ReflectWater-Main
    #define TREES //very cpu intensive
    #define ATMOSPHERE  //  freezes when no video acceleration is used
                        //  or as a user without access to video rights is used
    #define DECALS2       // simple decals
    //#define DECALS       //decalmanager sortof working slow tho
    #define TESSIMAGE
    #define FLARE
    #define FLARE2  // more realistic and working
    #define EDITOR
    #define FLAG    //
    #define FLAG2   //FMX
    #define COMPASS
    #define BOIDS
    #define TERRAIN
    #define occlusion
    #define FPSWEAPON // no uses diff event receiver than player so wont drive car or shoot cubes // screws with the flare2
    #define BULLETCAR // if FPSWEAPON is enabled the car wont work. diff event rec
    #define LOADLEVELS // dont use this without bullet or with occlusion its slow?
    #define BULLETBLEND
    #define RAG   //bulletRagdoll
    #define EXTRAS
    #define DESTRUCTION
    #define FORMATIONDEMO
    #define HUD
    #define Image2D // Just testing out
    #define CHOPPER
    #define  OPENSTEER
    #define VIDEO
    #define DSOUND
    #define PostProcess

// Include the headers for post processing
#include "../Scene/PostProcessing/CRendererPostProc.h"
#include "../Scene/PostProcessing/CEffectPostProc.h"
#include "../Scene/PostProcessing/CTransitionPostProc.h"
#include "../Scene/PostProcessing/CSplitPostProc.h"
#include "../Scene/PostProcessing/CLensFlarePostProc.h"
#include "../Scene/PostProcessing/CWaterPostProc.h"

#include "../Scene/CBeamSceneNode.h"
#include "../Scene/BoltSceneNode.h"
#include "../Physics/Ragdoll.h"
#include "../GUI/ChatBox/CGUIChatBox.h"

#include "../Scene/Obstacle.hpp"
#include "../Scene/Elevator.hpp"
#include "../Physics/Collision.hpp"
#include "../GUI/CHUD.h"
//#include "../GUI/CodeEditor/CGUIEditBoxIRB.h"
//CGUIEditBoxIRB * codeEditor;
#include "../Scene/tesselatedImage/tesselatedImage.h""
#include "../entities/chopper_control.h"
#include "../TerrainFactory/WaterNode/CReflectedWater.h"
#include "../TerrainFactory/water/RealisticWater.h"
//#include "../entities/player.h"
#include "../entities/OpenSteer/cOpenSteerDemo.h"
#undef useIrrExtensions13
#define HUD

#include "../TerrainFactory/realCloud/CloudSceneNode.h"

#ifdef VIDEO
    #include "../GUI/Video/CVideoMaster.h"
    //#include "GUI/Video/videoPlayer.h"
#endif

#include "../Scene/RibbonTrailSceneNode/RibbonTrailSceneNode.h"
RibbonTrailSceneNode* rt;

#include "../Events/InGameEventReceiver.h"
#include "../Scene/occlusion/Renderer.h"
#include "../Scene/Flag/SimpleFlag.h"
#include "../Scene/Flag/CFlagSceneNode.h"
#include "../entities/skeleton/Skeleton.h"

#include "../Physics/Vehicle.h"
#include "../entities/AI/recast_util.h"
    scene::ISceneNode* node = 0;
    scene::ISceneNode* naviNode = 0;
    RecastUtil* recast = 0;

#include "../Scene/particles.h"
#define SPARKA
    #ifdef SPARKA
        #include "../Scene/SPARK/SPK.h"
        #include "../Scene/SPARK/SPK_IRR.h"
        using namespace SPK;
        using namespace SPK::IRR;
//      #include "../Scene/RainMan.h"
    #endif

#include "../Input/Model/IrrAssimp/IrrAssimp.h"

#include "../GUI/cImage2D.h"
#include "../Scene/spriteManager/SpriteManager.h"
#include "../Scene/spriteManager/BmFont.h"
#include "../Scene/spriteManager/ParticleSystem.h"
#include "../GUI/Math/SCalcExpr.h"

#include "../TerrainFactory/FWGrass/GrassLoader.h"
#include "../TerrainFactory/FWGrass/gen/CGrassGenerator.h"
using namespace GrassGenerator;
#include "../TerrainFactory/ProceduralTrees/kornJungle/Jungle.h"
//#include "../Input/SQL/sqlCon.h"
#include <sqlite3.h>
    sqlite3_stmt* stmt;
char *zErrMsg;
  int rc;
//sqlite3 *db;
//#include <cwiid.h>
//#include "../Input/Controllers/wii/wii.h"

        CEffectPostProc* ppBlurDOF ;
         CEffectPostProc* ppBlur ;
         CEffectPostProc* ppMine;

    BmFont *fonts = new BmFont;

    SpriteManager *sprites = new SpriteManager;

    using namespace std;
    using namespace irr;

    btLogicManager* logicManager = new btLogicManager();
    static std::vector<RagDoll*> v_RagDolls;
    static std::vector<btRigidBody*> v_Boxes;
    irr::scene::ITriangleSelector* selecta = 0;

    scene::IMetaTriangleSelector* metaSelector;
  //  ICameraSceneNode* camera;
    scene::ITriangleSelector* selector;
    btTransform tr;

    scene::CCloudSceneNode* clouds;  ///bitplane clouds
    f32 rot=1.0;

    scene::CloudSceneNode* cloudLayer1;
    scene::CloudSceneNode* cloudLayer2;
    scene::CloudSceneNode* cloudLayer3;

#include "../Scene/flares/LensFlareSceneNode.h"
#include "../Scene/flares/SceneNodeAnimatorFollowCamera.h"
    scene::LensFlareSceneNode* lensFlareNode;
    scene::IMeshSceneNode* sunMeshNode;
    int bFlare2;
    #ifdef FLARE
    #endif
  //  scene::IMeshSceneNode* sunMeshNode;
    CLensFlareSceneNode *lensFlareNode2;
//    scene::LensFlareSceneNode* lensFlareNode;

#include "../GUI/sineGraph2d/SGraph2D.h"
#include "../GUI/widgets/CGUIBar.h"

  //  Vehicle *m_cVehicle;
  //  Vehicle *m_cVehicle2;

 //   static vector<Vehicle*> m_cVehicle;

    cSkeleton skeleton;
//        cAudio::IAudioManager* managerID;
//        cAudio::IAudioSource* mysound;


#include "PyMAIN.h"
#include "PyNet.h"
#define _GNU_SOURCE
//    #undef __cplusplus
#include "../Input/fluidsynthconfig.h"
#include "utils/fluidsynth_priv.h"
#if defined(HAVE_GETOPT_H)
#include <getopt.h>
#define GETOPT_SUPPORT 1
#endif

#include "fluidsynth.h"
//
#include "bindings/fluid_lash.h"
//
#ifndef WITH_MIDI
#define WITH_MIDI 1
#endif

fluid_cmd_handler_t* cmd_handler = NULL;

     fluid_settings_t* settings;
  fluid_player_t* player = NULL;
  fluid_midi_router_t* router = NULL;
  //fluid_sequencer_t* sequencer = NULL;
  fluid_midi_driver_t* mdriver = NULL;
  fluid_audio_driver_t* adriver = NULL;
  fluid_synth_t* synth = NULL;


PyMethodDef irr_function[] =
{
    {"delay",Python::PyIrr_Delay,METH_VARARGS,"delay"},
    {"sleep",Python::PyIrr_Sleep,METH_VARARGS,"sleep"},
    {"setTime",Python::PyIrr_setTime,METH_VARARGS,"setTime"},
    {"getTime",Python::PyIrr_getTime,METH_VARARGS,"getTime"},
    {"event",Python::PyIrr_Event,METH_VARARGS,"event"},

//        {"flare2",Python::PyIrr_Flare2,METH_VARARGS,"Loads Flare2"},


    {"formationdemo",Python::PyIrr_FormationDemo,METH_VARARGS,"Loads FormationDemo"},
    {"pauseGame",Python::PyIrr_pauseGame,METH_VARARGS,"pauseGame"},
    {"exit",Python::PyIrr_exit,METH_VARARGS,"exit"},
        {NULL,NULL,0,NULL}
};


void Python::registerIrrDevice(Luna *luna1,IrrlichtDevice &Device,InGameEventReceiver event){
    luna = luna1;
    device = &Device;
    driver = device->getVideoDriver();
    smgr   = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    mEvent = event;


  //  camera = smgr->addCameraSceneNodeFPS(0, 100, .050f, -1, luna->keyMap, 8);
//camera = smgr->addCameraSceneNode();


 //   camera->setFarValue(10000);
    //camera = smgr->addCameraSceneNodeFPS();
    //  camera->setFOV(PI/2);

    m_cScene = new Scene();
    m_cScene->registerIrrDevice(*device);
  //  m_cScene->setupLights();//Scene, setup for lights.
    int lastFPS = -1;
    u32 timeStamp = device-> getTimer()-> getRealTime(),deltaTime = 0;
    device->setEventReceiver ( &mEvent);
//    device->getCursorControl()->setVisible(false);
    Elevator::Instance()->Instance();
    ///Player::Instance()->Instance();//obsolete
    //    Collision::Instance()->Instance();
    ///Player::Instance()->setDevice(device); //obsolete
    //   Collision::Instance()->setDevice(device);

//    scene::IAnimatedMesh *mesh = (IAnimatedMesh*) smgr->getMesh("media/player/player.x");
//	scene::IAnimatedMeshSceneNode *skelNode = (IAnimatedMeshSceneNode*) smgr->addAnimatedMeshSceneNode(mesh);
	//cSkeleton skeleton; // moved externally
//	skeleton.Initialize(skelNode, 8);
	//core::vector3df pos = skeleton.getSkeletonSceneNode()->getPosition();
 //   skelNode->addShadowVolumeSceneNode();
//smgr->setShadowColor(video::SColor(150,0,0,0));
//smgr->addLightSceneNode(0, core::vector3df(0,0,0),video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 600.0f);
}

#include "PyScene.h"
// make a post draw loop instead of putting things into the checkkey

PyObject * Python::PyIrr_using(PyObject * self,PyObject * args){ //active camera
//ExecuteScript(irr::core::string<char> scriptname){
char * script;
char * arg;
    PyArg_ParseTuple(args,"ss",&script,&arg);

    ExecuteScript(script);
return Py_BuildValue("");
}

PyObject * Python::PyIrr_Delay(PyObject * self,PyObject * args){ //active camera
    //repurpose this for a path move delay
    float * delay;
    PyArg_ParseTuple(args,"f",&delay);
    device->sleep(delay);
return Py_BuildValue("");
}

PyObject * Python::PyIrr_Sleep(PyObject * self,PyObject * args){ //active camera
    int ammount;
    PyArg_ParseTuple(args,"i",&ammount);
    device->sleep(ammount);
return Py_BuildValue("");
}

PyObject * Python::PyIrr_setTime(PyObject * self,PyObject * args){ //active camera
    int ammount;
    PyArg_ParseTuple(args,"f",&ammount);

    //convert time here maybe provide a clock gui to use

    u32 timer=ammount;
    //device->sleep(ammount);
return Py_BuildValue("i",timer);
}

PyObject * Python::PyIrr_getTime(PyObject * self,PyObject * args){ //active camera
    int type;
    PyArg_ParseTuple(args,"i",&type);


     u32 tm = device->getTimer()->getRealTime();
    //device->sleep(ammount);
return Py_BuildValue("i",tm);
}

PyObject * Python::PyIrr_getScreen(PyObject * self,PyObject * args) {
    int type;
    PyArg_ParseTuple(args,"i",&type);
    if (type == 0){
        return Py_BuildValue("i",driver->getViewPort().getWidth());
    }
    else if (type == 1){

        return Py_BuildValue("i",driver->getViewPort().getHeight());
    }
//const irr::core::dimension2du& screenSize = driver->getScreenSize();
//irr::core::vector2df screenSize(driver.getViewPort().getWidth(), driver.getViewPort().getHeight());

}
PyObject * Python::PyIrr_fpsWeapon(PyObject * self,PyObject * args){
// need to attach to bones and/or nodes here
bFPS = 1;
    long pcam;
    PyArg_ParseTuple(args,"l",&pcam);
    ICameraSceneNode* camera = pcam;
    device->getGUIEnvironment()->addImage( driver->getTexture("data/textures/crosshairs/crosshair1.png"),
                                            core::position2d<s32>((luna->resolution[0]/2)-64,(luna->resolution[1]/2)-64));
    #ifdef FPSWEAPON
          IAnimatedMesh*   gunmesh = smgr->getMesh("data/models/weapons/M4/3d_person/M4A1d.3ds");
          scene::IAnimatedMeshSceneNode* agun;
          agun = smgr->addAnimatedMeshSceneNode(gunmesh);
          if (agun)
          {
            agun->setMaterialTexture(0, driver->getTexture("data/models/weapons/M4/1st_person/M4A1.jpg"));
            agun->setScale(core::vector3df(1.2f, 1.2f, 1.2f));
            agun->setPosition(core::vector3df(180.f,1.5f,0.f));
            agun->setRotation(core::vector3df(0.f,0.f,90.f));
            //agun->apply_light2node(agun);
        	agun->addShadowVolumeSceneNode();
          }
          gunmesh->drop();
       // scene::ICameraSceneNode* cam = smgr->addCameraSceneNodeFPS(0, 100.0f, .5f,-1,keyMap,8);
                                  // cam->setPosition(core::vector3df(-200,100,200));
                                 //  cam->setTarget(core::vector3df(0,0,0));
        camera->setFOV(PI/2);
        camera->setFarValue(7000);


        M4 = new firstPersonWeapon(device, camera);
        //  apply_light2node(M4->getNode());
        device->setEventReceiver(M4);
      //  return Py_BuildValue("l",agun);
    #endif
return Py_BuildValue("");
}

PyObject * Python::PyIrr_addPlayer(PyObject * self,PyObject * args) {//active camera
   #ifdef PLAYER
         luna->m_cPlayer = new Player();
         luna->m_cPlayer->registerIrrlichtDevice(luna->frameDeltaTime,*device);
         luna->m_cPlayer->initialize();
         luna->m_cPlayer->setParent(smgr->getActiveCamera());
         //Collision::Instance()->createPlayerCollision();
            //m_cPlayer->createShadow();
        luna->m_cPlayer->CheckFalling();

       // scene::ILightSceneNode* light1 =
      //      smgr->addLightSceneNode(0, core::vector3df(0,60,0),
      //      video::SColorf(0.5f, 1.0f, 0.5f, 0.0f), 800.0f);

      return Py_BuildValue("l",m_cPlayer);  //return the handle
    #endif
return Py_BuildValue("");
}

PyObject * Python::PyIrr_DecalManager(PyObject * self,PyObject * args){ //active camera
    long * node;
    int type;
	PyArg_ParseTuple(args,"i",&type);

	if (type){
    bDecals=1; // should fix this to be inside the defines
    #ifdef DECALS
        //! Create decal manager
        decalManager = new DecalManager(smgr);
        //device->getSceneManager()->createMetaTriangleSelector();
    return Py_BuildValue("l",decalManager);
    #endif
	}else{
    #ifdef DECALS2
    bDecals=2;
        video::ITexture* image = driver->getTexture("./data/textures/bullet.png");
        for(int i=0; i<MAX_DECALS; i++){
            decals[i] = new ArmDecalSceneNode(smgr->getRootSceneNode(), smgr, image, 15.2f);
        //decals[i]->setMaterialType( video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        //decals[i]->setMaterialType( video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF );
        //decals->setMaterialFlag(video::EMF_LIGHTING, true);
        //decals[i]->getMaterial(0)->setFlag();
        }
        int nextDecal=0;
    return Py_BuildValue("1");
    #endif
	}
return Py_BuildValue("0");
}

PyObject * Python::PyIrr_Event(PyObject * self,PyObject * args){
	//long * event;
	int id;
	PyArg_ParseTuple(args,"i",&id);
//IEventReceiver *event2=event;
	//setevent
	//return events
if  (id == 1){

	return Py_BuildValue("i",mEvent.eid);
}
if  (id == 0){

	return Py_BuildValue("s",mEvent.levent);
}
		return Py_BuildValue("");

}

PyObject * Python::PyIrr_Delete(PyObject * self,PyObject * args){ //active camera

	long * node;
	PyArg_ParseTuple(args,"l",&node);
	delete node;

}

PyObject * Python::PyIrr_pauseGame(PyObject * self,PyObject * args){
    luna->m_cInGameEvents.Quit=true;
return Py_BuildValue("");
}


PyObject * Python::PyIrr_exit(PyObject * self,PyObject * args){
    luna->m_cInGameEvents.Quit=true;
    return Py_BuildValue("");
}

#include "../Scripting/Environmental.h"
#include "../Scripting/PyExtras.h"
#include "../Scripting/PY_Physics.h"
#include "../Scripting/PyImage.h"
#include "PyMath.h"
#include "PySound.h"
#include "PyCamera.h"
#include "PyInput.h"
#include "PyGUI.h"

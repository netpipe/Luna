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
#include "../Net/CGUIChatBox.h"

#include "../Scene/Obstacle.hpp"
#include "../Scene/Elevator.hpp"
#include "../Physics/Collision.hpp"
#include "../GUI/CHUD.h"
#include "../GUI/CodeEditor/CGUIEditBoxIRB.h"
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

#include "../TerrainFactory/ProceduralTrees/kornJungle/Jungle.h"
//#include <cwiid.h>
//#include "../Input/Controllers/wii/wii.h"

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

  //  Vehicle *m_cVehicle;
  //  Vehicle *m_cVehicle2;

 //   static vector<Vehicle*> m_cVehicle;

    cSkeleton skeleton;
//        cAudio::IAudioManager* managerID;
//        cAudio::IAudioSource* mysound;


#include "PyMAIN.h"
#include "PyNet.h"


PyMethodDef irr_Scene[] =
{
/*
startphysics
loadlevel - subloader for tracks or levels
ragdoll - needs a manager
network connect / info / manager interface
script reload and compile function
reminder to actually check the names match with unstable ide's and whatnot
*/

	{"drawtext",Python::PyIrr_DrawText,METH_VARARGS,"Renders text to the screen with default font"},
	{"add_cube",Python::PyIrr_AddCubeSceneNode,METH_VARARGS,"Adds a cube scene node"},
	{"load_texture",Python::PyIrr_LoadTexture,METH_VARARGS,"Loads a texture"},
	{"set_texture",Python::PyIrr_SetTexture,METH_VARARGS,"Adds a texture to a scene node"},
    {"addCamera",Python::PyIrr_addCamera,METH_VARARGS,"sets camera vector"},
    {"setCamera",Python::PyIrr_SetCamera,METH_VARARGS,"sets camera vector"},
	{"getCamera",Python::PyIrr_GetCamera,METH_VARARGS,"getcamera vector"},
	{"Reset",Python::PyIrr_Reset,METH_VARARGS,"Reset various parts of scripting system"},
	{"addAMesh",Python::PyIrr_addAnimatedMesh,METH_VARARGS,"PyIrr_addAnimatedMesh"},
	{"addMesh",Python::PyIrr_LoadMesh,METH_VARARGS,"PyIrr_addMesh"},
    {"addModel",Python::PyIrr_loadModel,METH_VARARGS,"load model"},
    {"loadTrack",Python::PyIrr_LoadTrack,METH_VARARGS,"load model"},
    {"loadLevel",Python::PyIrr_LoadLevel,METH_VARARGS,"load model"},
    {"Light",Python::PyIrr_Light,METH_VARARGS,"load model"},
	//input
    {"using",Python::PyIrr_using,METH_VARARGS,"for opening scripts within scripts"},
    {"recast",Python::PyIrr_recast,METH_VARARGS,"recast navigation"},
    {"addWheel",Python::PyIrr_recast,METH_VARARGS,"recast navigation"},
    {"media",Python::PyIrr_media,METH_VARARGS,"media"},


	//scene
    {"tesselate",Python::PyIrr_tesselateImage,METH_VARARGS,"PyIrr_tesselateImage"},
    {"atmosphere",Python::PyIrr_atmosphere,METH_VARARGS,"PyIrr_atmosphere"},
    {"soundman",Python::PyIrr_SoundMan,METH_VARARGS,"PyIrr_SoundMan"},
    {"addvideo",Python::PyIrr_addVideo,METH_VARARGS,"PyIrr_addVideo"},
    {"decals",Python::PyIrr_DecalManager,METH_VARARGS,"PyIrr_DecalManager"},
    {"addwater",Python::PyIrr_WaterPlane,METH_VARARGS,"water plane reflective"},
    {"setPosition",Python::PyIrr_setPosition,METH_VARARGS,"setPosition"},
    {"getPosition",Python::PyIrr_getPosition,METH_VARARGS,"getPosition"},
    {"addSphereNode",Python::PyIrr_addSphereNode,METH_VARARGS,"addSphereNode"},
    {"aBillBoard",Python::PyIrr_aBillBoard,METH_VARARGS,"billboard"},
    {"addTerrain",Python::PyIrr_addTerrain,METH_VARARGS,"PyIrr_addTerrain"},
    {"addTree",Python::PyIrr_Trees,METH_VARARGS,"PyIrr_addTree"},
	{"addHUD",Python::PyIrr_addHUD,METH_VARARGS,"PyIrr_addHUD"},
    {"exportScene",Python::PyIrr_ExportScene,METH_VARARGS,"PyIrr_ExportScene"},



    //Physics
    {"setVelocity",Python::PyIrr_setVelocity,METH_VARARGS,"setVelocity"},
    {"motionTrail",Python::PyIrr_motionTrail,METH_VARARGS,"motionTrail"},
    {"calculate",Python::PyIrr_calcMath,METH_VARARGS,"calculate"},
    //Timers
    {"delay",Python::PyIrr_Delay,METH_VARARGS,"delay"},
    {"sleep",Python::PyIrr_Sleep,METH_VARARGS,"sleep"},
    {"setTime",Python::PyIrr_setTime,METH_VARARGS,"setTime"},
    {"getTime",Python::PyIrr_getTime,METH_VARARGS,"getTime"},
    //gui

    {"chatbox",Python::PyIrr_ChatBox,METH_VARARGS,"chatbox for chatting in/with/alone"},
//  {"render",Python::PyIrr_Render,METH_VARARGS,"PyIrr_Render"}
//  {"chatbox",Python::PyIrr_Terrain,METH_VARARGS,"pyterrain"},
    {"pauseGame",Python::PyIrr_pauseGame,METH_VARARGS,"pauseGame"},
    {"exit",Python::PyIrr_exit,METH_VARARGS,"exit"},
    {"SPARK",Python::PyIrr_SPARKA,METH_VARARGS,"SPARK MANAGER"},
    {"delete",Python::PyIrr_Delete,METH_VARARGS,"delete"},

	{NULL,NULL,0,NULL}
};

PyMethodDef irr_fun2[] =
{
//        {"flare2",Python::PyIrr_Flare2,METH_VARARGS,"Loads Flare2"},
        {"formationdemo",Python::PyIrr_FormationDemo,METH_VARARGS,"Loads FormationDemo"},
        {"set_texture",Python::PyIrr_SetTexture,METH_VARARGS,"Adds a texture to a scene node"},
        {"image2d",Python::PyIrr_2Dimage,METH_VARARGS,"PyIrr_2Dimage"},
        {NULL,NULL,0,NULL}
};

PyMethodDef irr_Input[] =
{
    {"getKey",Python::PyIrr_getKey,METH_VARARGS,"get key state"},
    {"wii",Python::PyIrr_wii,METH_VARARGS,"wiimote access"},
    {"gamepad",Python::PyIrr_gamePad,METH_VARARGS,"gamepad"},
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
    device->setEventReceiver ( &mEvent);
    m_cScene = new Scene();
    m_cScene->registerIrrDevice(*device);
    m_cScene->setupLights();//Scene, setup for lights.
    int lastFPS = -1;
    u32 timeStamp = device-> getTimer()-> getRealTime(),deltaTime = 0;

	// some lights
	video::SLight l;
	scene::ILightSceneNode *light = smgr->addLightSceneNode(0,core::vector3df(50,100,50),video::SColorf(1,1,1,1.f),100);
	l = light->getLightData();
	l.Type = video::ELT_POINT;
	l.AmbientColor = video::SColorf(.35,.35,.35);
	l.SpecularColor = video::SColorf(.7,.7,.5);
	l.DiffuseColor = video::SColorf(1,1,1);
	l.CastShadows = true;
	light->setLightData( l );
//    scene::ILightSceneNode* light = smgr->addLightSceneNode( 0, core::vector3df(100,400,100),video::SColorf(1,1,1,1), 10.0f );
 //   smgr->addLightSceneNode(NULL, core::vector3df(0,100,0), video::SColorf(1.f, 1.f, 1.f), 2500, -1);

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

PyObject * Python::PyIrr_SoundMan(PyObject * self,PyObject * args){ //active camera

    int param,state,sound,ammount;
    PyArg_ParseTuple(args,"liii",&sound,&param,&ammount,&state);

    #ifdef DSOUND
    // sound intensity for raycasted sound.  // surfaceRoughnessHardness/propigation factor, distance,handle
    switch (param){
    case 0:
//        managerID = cAudio::createAudioManager(true);  // broken has to be done from main
       if( managerID)
        {
         //   luna->manager->initialize(luna->manager->getAvailableDeviceName(0));
           mysound = managerID->create("bling","./media/bling.ogg",false);
    //        return Py_BuildValue("l",manager
            mysound->play2d(true);
        }

       return Py_BuildValue("l",managerID);
        //break;
    case 1:
            mysound = managerID->create("bling","./media/bling.ogg",false);

       return Py_BuildValue("l",mysound);
        break;
    }
    #endif
return Py_BuildValue("l",managerID);
}// make add sound method

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
    bDecals=1; // should fix this to be inside the defines
    #ifdef DECALS
        //! Create decal manager
        decalManager = new DecalManager(smgr);
        //device->getSceneManager()->createMetaTriangleSelector();
    return Py_BuildValue("l",decalManager);
    #endif

    #ifdef DECALS2
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
return Py_BuildValue("0");
}

PyObject * Python::PyIrr_Delete(PyObject * self,PyObject * args){ //active camera

	long * node;
	PyArg_ParseTuple(args,"l",&node);
	delete node;

}
#include "../Scripting/Environmental.h"
#include "../Scripting/PyExtras.h"
#include "../Scripting/PY_Physics.h"
#include "../Scripting/PyImage.h"
#include "PyCamera.h"
#include "PyInput.h"
#include "PyGUI.h"

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
    {"SPARK",Python::PyIrr_SPARKA,METH_VARARGS,"SPARK MANAGER"},
    {"grass",Python::PyIrr_FWGrass,METH_VARARGS,"grass"},
    {"postprocess",Python::PyIrr_PostProcess,METH_VARARGS,"postProcess"},
    {"fluidsynth",Python::PyIrr_FluidSynth,METH_VARARGS,"fluidsynth"},





    //Physics
    {"setVelocity",Python::PyIrr_setVelocity,METH_VARARGS,"setVelocity"},
    {"motionTrail",Python::PyIrr_motionTrail,METH_VARARGS,"motionTrail"},
    {"calculate",Python::PyIrr_calcMath,METH_VARARGS,"calculate"},
    //Timers
    {"delay",Python::PyIrr_Delay,METH_VARARGS,"delay"},
    {"sleep",Python::PyIrr_Sleep,METH_VARARGS,"sleep"},
    {"setTime",Python::PyIrr_setTime,METH_VARARGS,"setTime"},
    {"getTime",Python::PyIrr_getTime,METH_VARARGS,"getTime"},

    {"delete",Python::PyIrr_Delete,METH_VARARGS,"delete"},
    {"pauseGame",Python::PyIrr_pauseGame,METH_VARARGS,"pauseGame"},
    {"exit",Python::PyIrr_exit,METH_VARARGS,"exit"},

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
   // device->setEventReceiver ( &mEvent);
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

PyObject * Python::PyIrr_FluidSynth(PyObject * self,PyObject * args){ //active camera

//http://www.fluidsynth.org/api/index.html#MIDIPlayerMem
    int typee;
    char * sound;
    char * param;
    PyArg_ParseTuple(args,"ssi",&sound,&param,&typee);
#define NETWORK_SUPPORT

	//char *psoundfont ="soundfonts/VintageDreamsWaves-v2.sf2";
		char *psoundfont =sound;
	//char *psong = "BLUES.MID";
     char *psong = param;


if( typee==0 ){



     //   int param,state,sound,ammount;
   // PyArg_ParseTuple(args,"liii",&sound,&param,&ammount,&state);
   //load unload
     fluid_settings_t* settings;
//  int arg1 = 1;
  char buf[512];
//  int c, i;
  int interactive = 1;
  int midi_in = 1;

#ifdef NETWORK_SUPPORT
  fluid_server_t* server = NULL;
  int with_server = 0;
#endif
  char* config_file = NULL;
  int audio_groups = 0;
  int audio_channels = 0;
  int dump = 0;
  int fast_render = 0;
  static const char optchars[] = "a:C:c:dE:f:F:G:g:hijK:L:lm:nO:o:p:R:r:sT:Vvz:";
#ifdef LASH_ENABLED
  int connect_lash = 1;
  int enabled_lash = 0;		/* set to TRUE if lash gets enabled */
  fluid_lash_args_t *lash_args;

  lash_args = fluid_lash_extract_args (&argc, &argv);
#endif



  settings = new_fluid_settings();


 /* The 'groups' setting is relevant for LADSPA operation and channel mapping
   * in rvoice_mixer.
   * If not given, set number groups to number of audio channels, because
   * they are the same (there is nothing between synth output and 'sound card')
   */
  if ((audio_groups == 0) && (audio_channels != 0)) {
      audio_groups = audio_channels;
  }
  if (audio_groups != 0)
  {
      fluid_settings_setint(settings, "synth.audio-groups", audio_groups);
  }

  if (fast_render) {
    midi_in = 0;
    interactive = 0;
#ifdef NETWORK_SUPPORT
    with_server = 0;
#endif
    fluid_settings_setstr(settings, "player.timing-source", "sample");
    fluid_settings_setint(settings, "synth.lock-memory", 0);
  }

  /* create the synthesizer */
  synth = new_fluid_synth(settings);
  if (synth == NULL) {
    fprintf(stderr, "Failed to create the synthesizer\n");
    exit(-1);
  }


  /* load the soundfonts (check that all non options are SoundFont or MIDI files) */
//  for (i = arg1; i < argc; i++) {
    if (fluid_is_soundfont(psoundfont))
    {
      if (fluid_synth_sfload(synth, psoundfont, 1) == -1)
	fprintf(stderr, "Failed to load the SoundFont %s\n", psoundfont);
    }
    else if (!fluid_is_midifile(psoundfont))
      fprintf (stderr, "Parameter '%s' not a SoundFont or MIDI file or error occurred identifying it.\n",
	       psoundfont);


  /* start the synthesis thread */
  if (!fast_render) {
		fluid_settings_setstr(settings, "audio.driver", "alsa");
    adriver = new_fluid_audio_driver(settings, synth);
    if (adriver == NULL) {
      fprintf(stderr, "Failed to create the audio driver\n");
//      goto cleanup;
    }
  }


  /* start the midi router and link it to the synth */
#if WITH_MIDI
  if (midi_in) {
    /* In dump mode, text output is generated for events going into and out of the router.
     * The example dump functions are put into the chain before and after the router..
     */
    //sequencer = new_fluid_sequencer2(0);

    router = new_fluid_midi_router(
      settings,
      dump ? fluid_midi_dump_postrouter : fluid_synth_handle_midi_event,
      (void*)synth);

    if (router == NULL) {
      fprintf(stderr, "Failed to create the MIDI input router; no MIDI input\n"
	      "will be available. You can access the synthesizer \n"
	      "through the console.\n");
    } else {
      mdriver = new_fluid_midi_driver(
	settings,
	dump ? fluid_midi_dump_prerouter : fluid_midi_router_handle_midi_event,
	(void*) router);
      if (mdriver == NULL) {
	fprintf(stderr, "Failed to create the MIDI thread; no MIDI input\n"
		"will be available. You can access the synthesizer \n"
		"through the console.\n");
      }
    }
  }
#endif

  /* play the midi fildes, if any */
//  for (i = arg1; i < argc; i++) {
    if  (fluid_is_midifile(psong)) {

      if (player == NULL) {
	player = new_fluid_player(synth);
	if (player == NULL) {
	  fprintf(stderr, "Failed to create the midifile player.\n"
		  "Continuing without a player.\n");
	//  break;
	}
      }

      fluid_player_add(player, psong);
    }
 // }

  if (player != NULL) {

    if (fluid_synth_get_sfont(synth, 0) == NULL) {
      /* Try to load the default soundfont if no soundfont specified */
      char *s;
      if (fluid_settings_dupstr(settings, "synth.default-soundfont", &s) != FLUID_OK)
        s = NULL;
      if ((s != NULL) && (s[0] != '\0'))
        fluid_synth_sfload(synth, s, 1);

      FLUID_FREE(s);
    }
   //  fluid_player_set_bpm (player,125);

  //  fluid_player_set_loop(player,5);
  //  fluid_player_play(player);
    //fluid_player_set_midi_tempo(player,480000);
//fluid_player_join(player);
  }


  cmd_handler = new_fluid_cmd_handler(synth, router);
  if (cmd_handler == NULL) {
    fprintf(stderr, "Failed to create the command handler\n");
 //   goto cleanup;
  }

  /* try to load the user or system configuration */
  if (config_file != NULL) {
    fluid_source(cmd_handler, config_file);
  } else if (fluid_get_userconf(buf, sizeof(buf)) != NULL) {
    fluid_source(cmd_handler, buf);
  } else if (fluid_get_sysconf(buf, sizeof(buf)) != NULL) {
    fluid_source(cmd_handler, buf);
  }

  /* run the server, if requested */
#ifdef NETWORK_SUPPORT
  if (with_server) {
    server = new_fluid_server(settings, synth, router);
    if (server == NULL) {
      fprintf(stderr, "Failed to create the server.\n"
	     "Continuing without it.\n");
    }
  }
#endif

#ifdef LASH_ENABLED
  if (enabled_lash)
    fluid_lash_create_thread (synth);
#endif

//          fluid_player_play(player);
}

else if (typee == 1){
//fluid_player_stop(player);
//fluid_player_join(player);

            /* Play a note */
        fluid_synth_noteon(synth, 0, 60, 100);
}
else if (typee == 2){
fluid_player_stop(player);
//fluid_player_join(player);

}

else if (typee == 3){
    //        printf("ready and playing");
  //          fluid_player_stop(player);
//        fluid_player_join(player);
if (fluid_player_get_status(player) == FLUID_PLAYER_READY )
{
    printf("ready and playing");

        fluid_player_add(player,param);
        fluid_player_play(player);
    }
if (fluid_player_get_status(player) == FLUID_PLAYER_DONE )
{
    printf("done and replaying");

        fluid_player_add(player,param);
        fluid_player_play(player);
    }
//if  (fluid_is_midifile(psong)) {
//
//      if (player == NULL) {
//	player = new_fluid_player(synth);
//	if (player == NULL) {
//	  fprintf(stderr, "Failed to create the midifile player.\n"
//		  "Continuing without a player.\n");
//	//  break;
//	}
//      }
//
//      fluid_player_add(player, psong);
//          fluid_player_play(player);
//    }


       // fluid_player_join(player);
//    if (fluid_file_renderer_process_block(renderer) != FLUID_OK)
//    {
//        break;
    }

else if (typee == 4){
    printf("playing");
      //  fluid_player_join(player);
      //  fluid_player_add(player,param);
      //  fluid_player_play(player);
//if (fluid_player_get_status(player) == FLUID_PLAYER_PLAYING)
//{
//    if (fluid_file_renderer_process_block(renderer) != FLUID_OK)
//    {
//        break;
//    }
//}
}

else if (typee == 6){ // render audio to file.
//  if (fast_render) {
//    char *filename;
//    if (player == NULL) {
//      fprintf(stderr, "No midi file specified!\n");
//      goto cleanup;
//    }
//
//    fluid_settings_dupstr (settings, "audio.file.name", &filename);
//    printf ("Rendering audio to file '%s'..\n", filename);
//    if (filename) FLUID_FREE (filename);
//
//    fast_render_loop(settings, synth, player);
//  }
}



else if (typee == 5){
#ifdef NETWORK_SUPPORTs
  if (server != NULL) {
    /* if the user typed 'quit' in the shell, kill the server */
    if (!interactive) {
      fluid_server_join(server);
    }
    delete_fluid_server(server);
  }
#endif

  if (cmd_handler != NULL) {
    delete_fluid_cmd_handler(cmd_handler);
  }

  if (player != NULL) {

      fluid_player_stop(player);
   // }
//    if (adriver != NULL || !fluid_settings_str_equal(settings, "player.timing-source", "sample")) {
//      /* if no audio driver and sample timers are used, nothing makes the player advance */
//      fluid_player_join(player);
//    }
    delete_fluid_player(player);
  }

  if (router) {
#if WITH_MIDI
    if (mdriver) {
      delete_fluid_midi_driver(mdriver);
    }
    delete_fluid_midi_router(router);
#endif
  }

  /*if (sequencer) {
    delete_fluid_sequencer(sequencer);
  }*/

  if (adriver) {
    delete_fluid_audio_driver(adriver);
  }

  if (synth) {
    delete_fluid_synth(synth);
  }

  if (settings) {
    delete_fluid_settings(settings);
  }
}

//fluid_settings_setstr(settings, "audio.file.name", "/path/to/output.wav");


return Py_BuildValue("");
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

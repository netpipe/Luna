///Main Python Function Includes
///Stuff Relivent to Initialization and management of scene / sound and managers.

// there are scripting includes at the bottom for scripting system to register in pythonManager.h
// there are includes at bottom of file for scripting too.
#include "../config.h"
//#define SOUND
//#include "../Luna.h"
#include <cstdlib>
    #define MAX_DECALS 50

    using namespace std;
    using namespace irr;

#ifdef PostProcess
// Include the headers for post processing
#include "../Scene/PostProcessing/CRendererPostProc.h"
#include "../Scene/PostProcessing/CEffectPostProc.h"
#include "../Scene/PostProcessing/CTransitionPostProc.h"
#include "../Scene/PostProcessing/CSplitPostProc.h"
#include "../Scene/PostProcessing/CLensFlarePostProc.h"
#include "../Scene/PostProcessing/CWaterPostProc.h"
#endif

#ifdef EXTRAS
#include "../Scene/CBeamSceneNode.h"
#include "../Scene/BoltSceneNode.h"
#include "../GUI/ChatBox/CGUIChatBox.h"
#endif

#ifdef RAGDOLL
#include "../Physics/Ragdoll.h"
#endif

#ifdef FPS
#include "../Scene/Obstacle.hpp"
#include "../Scene/Elevator.hpp"
#include "../Physics/Collision.hpp"
#endif

#ifdef HUD
#include "../GUI/CHUD.h"
#endif

#ifdef CODEEDITOR2
#include "../GUI/CodeEditor/CGUIEditBoxIRB.h"
#endif // CODEEDITOR
//CGUIEditBoxIRB * codeEditor;

#ifdef TESSELATE
#include "../Scene/tesselatedImage/tesselatedImage.h"
#endif

#ifdef CHOPPER
#include "../entities/chopper_control.h"
#endif

#ifdef WATER
    #ifdef ReflevtiveWater
        //#include "../TerrainFactory/WaterNode/CReflectedWater.h"
    #endif

    #include "../TerrainFactory/water/RealisticWater.h"
#endif

#ifdef OPENSTEER
    //#include "../entities/player.h"
    #include "../entities/OpenSteer/cOpenSteerDemo.h"
    #undef useIrrExtensions13
    #define HUD //not sure if this is needed ?
#endif

#ifdef ATMOSPHERE
    #include "../TerrainFactory/realCloud/CloudSceneNode.h"
#endif

#ifdef VIDEO
    #include "../GUI/Video/CVideoMaster.h"
   //#include "../GUI/Video/videoPlayer.h"
#endif

#ifdef RIBBONTRAIL
    #include "../Scene/RibbonTrailSceneNode/RibbonTrailSceneNode.h"
    RibbonTrailSceneNode* rt;
#endif

#ifdef EVENTS
    #include "../Events/InGameEventReceiver.h"
#endif

#ifdef OCCLUSION
    #include "../Scene/occlusion/Renderer.h"
#endif

#ifdef FLAG
    #include "../Scene/Flag/SimpleFlag.h"
    #include "../Scene/Flag/CFlagSceneNode.h"
#endif
#ifdef SKELETON
    #include "../entities/skeleton/Skeleton.h"
#endif

#ifdef PHYSICS
    #include "../Physics/Vehicle.h"
#endif

#ifdef RECAST
#include "../entities/AI/recast_util.h"
    scene::ISceneNode* node = 0;
    scene::ISceneNode* naviNode = 0;
    RecastUtil* recast = 0;
#endif


#ifdef SPARK
    #include "../Scene/SPARK/SPK.h"
    #include "../Scene/SPARK/SPK_IRR.h"
    using namespace SPK;
    using namespace SPK::IRR;
    //#include "../Scene/RainMan.h"
    //#include "../Scene/particles.h"
#endif

#ifdef ASSIMP
    #include "../Input/Model/IrrAssimp/IrrAssimp.h"
#endif

#ifdef Image2D
    #include "../GUI/cImage2D.h"
#endif

#ifdef FT2
    #include "../Scene/spriteManager/BmFont.h"
#endif // FT2

#ifdef SPRITES
    #include "../Scene/spriteManager/SpriteManager.h"
    #include "../Scene/spriteManager/ParticleSystem.h"
#endif

#ifdef SCALC
    #include "../GUI/Math/SCalcExpr.h"
#endif

#ifdef VEGETATION
    #include "../TerrainFactory/FWGrass/GrassLoader.h"
    #include "../TerrainFactory/FWGrass/gen/CGrassGenerator.h"
    using namespace GrassGenerator;
#endif

#ifdef TREES
    #include "../TerrainFactory/ProceduralTrees/kornJungle/Jungle.h"
#endif // TREES

#ifdef SQLITE
    //#include "../Input/SQL/sqlCon.h"
    #include "../Input/sqlite/sqlite3.h"
    sqlite3_stmt* stmt;
    char *zErrMsg;
    int rc;
//sqlite3 *db;
#endif

//#include <cwiid.h>
//#include "../Input/Controllers/wii/wii.h"
#ifdef PostProcess
    CEffectPostProc* ppBlurDOF ;
    CEffectPostProc* ppBlur ;
    CEffectPostProc* ppMine;
    CEffectPostProc* ppInvert;
#endif

#ifdef FT2
    BmFont *bmfonts = new BmFont;
#endif

#ifdef SPRITES
    SpriteManager *sprites = new SpriteManager;
#endif

#ifdef PHYSICS
    #ifdef RAGDOLL
        static std::vector<RagDoll*> v_RagDolls;
    #endif

    #ifdef BULLETBLEND
        btLogicManager* logicManager = new btLogicManager();
        static std::vector<btRigidBody*> v_Boxes;
    #endif

     btTransform tr;
#endif

    irr::scene::ITriangleSelector* selecta = 0;

    scene::IMetaTriangleSelector* metaSelector;
  //  ICameraSceneNode* camera;
    scene::ITriangleSelector* selector;


#ifdef CLOUDS
    scene::CCloudSceneNode* clouds;  ///bitplane clouds
    f32 rot=1.0;

    scene::CloudSceneNode* cloudLayer1;
    scene::CloudSceneNode* cloudLayer2;
    scene::CloudSceneNode* cloudLayer3;
#endif

#ifdef FLARE
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
#endif

#ifdef SGRAPH2D
    #include "../GUI/sineGraph2d/SGraph2D.h"
#endif

#include "../GUI/widgets/CGUIBar.h"

//Vehicle *m_cVehicle;
//Vehicle *m_cVehicle2;
//static vector<Vehicle*> m_cVehicle;

#ifdef SKELETON
    cSkeleton skeleton;
#endif

//cAudio::IAudioManager* managerID;
//cAudio::IAudioSource* mysound;


#ifdef BOX2DLITE
    #include "../Physics/box2D.h"
#endif

#ifdef PYTHON
    #include "PyMAIN.h"
    #include "PyNet.h"
    #define _GNU_SOURCE
    //    #undef __cplusplus

    #if defined(HAVE_GETOPT_H)
        #include <getopt.h>
        #define GETOPT_SUPPORT 1
    #endif

    #ifdef __EMSCRIPTEN__
    ////#include "fluidlite.h"
        #ifdef FLUIDSYNTH
            #include "../Input/fluidsynthconfig.h"
            #include "src/utils/fluidsynth_priv.h"
            #include "fluidsynth.h"
                //
            #include "src/bindings/fluid_lash.h"
        #endif
    #else
    #ifdef FLUIDSYNTH
            #include "../Input/fluidsynthconfig.h"
            #include "src/utils/fluidsynth_priv.h"
            #include "fluidsynth.h"
            #include "src/bindings/fluid_lash.h"
    #endif //fluidsynth
    #endif //emscripten

#endif //python

//#ifdef AgAudio
////Sound *m_sound;
//Sound *m_sound;
//Sound m_default_sound_buffer;
//#endif

#ifdef FLUIDSYNTH
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
#endif

#ifdef FT2
    CGUITTFont *fonts[6],*font,*font2;
    CGUITTFace face,face2,face3;
#endif

#ifdef PYTHON
PyMethodDef irr_function[] =
{
    {"getstring",Python::PyIrr_GetString,METH_VARARGS,"getstring"},
    {"delay",Python::PyIrr_Delay,METH_VARARGS,"delay"},
    {"sleep",Python::PyIrr_Sleep,METH_VARARGS,"sleep"},
    {"setTime",Python::PyIrr_setTime,METH_VARARGS,"setTime"},
    {"getTime",Python::PyIrr_getTime,METH_VARARGS,"getTime"},
    {"event",Python::PyIrr_Event,METH_VARARGS,"event"},
    {"delete",Python::PyIrr_Delete,METH_VARARGS,"delete"},
//{"flare2",Python::PyIrr_Flare2,METH_VARARGS,"Loads Flare2"},
    {"wayman",Python::PyIrr_WayPoint,METH_VARARGS,"waypoint manager"},
    {"pauseGame",Python::PyIrr_pauseGame,METH_VARARGS,"pauseGame"},
    {"exit",Python::PyIrr_exit,METH_VARARGS,"exit"},
    {"exec",Python::PyIrr_exec,METH_VARARGS,"exec"},
    {NULL,NULL,0,NULL}
};

//https://www.dreamincode.net/forums/topic/157186-conversion-of-string-to-enum/
std::map< std::string, EKEY_CODE > keydictionary;
void Python::initkeys(){
keydictionary["KEY_LBUTTON"] = KEY_LBUTTON;
keydictionary["KEY_RBUTTON"] = KEY_RBUTTON;
keydictionary["KEY_CANCEL"] = KEY_CANCEL;
keydictionary["KEY_MBUTTON"] = KEY_MBUTTON;
keydictionary["KEY_XBUTTON1"] = KEY_XBUTTON1;
keydictionary["KEY_XBUTTON2"] = KEY_XBUTTON2;
keydictionary["KEY_BACK"] = KEY_BACK;
keydictionary["KEY_TAB"] = KEY_TAB;
keydictionary["KEY_CLEAR"] = KEY_CLEAR;
keydictionary["KEY_RETURN"] = KEY_RETURN;
keydictionary["KEY_SHIFT"] = KEY_SHIFT;
keydictionary["KEY_CONTROL"] = KEY_CONTROL;
keydictionary["KEY_MENU"] = KEY_MENU;
keydictionary["KEY_PAUSE"] = KEY_PAUSE;
keydictionary["KEY_CAPITAL"] = KEY_CAPITAL;
keydictionary["KEY_KANA"] = KEY_KANA;
keydictionary["KEY_HANGUEL"] = KEY_HANGUEL;
keydictionary["KEY_HANGUL"] = KEY_HANGUL;
keydictionary["KEY_JUNJA"] = KEY_JUNJA;
keydictionary["KEY_FINAL"] = KEY_FINAL;
keydictionary["KEY_HANJA"] = KEY_HANJA;
keydictionary["KEY_KANJI"] = KEY_KANJI;
keydictionary["KEY_ESCAPE"] = KEY_ESCAPE;
keydictionary["KEY_CONVERT"] = KEY_CONVERT;
keydictionary["KEY_NONCONVERT"] = KEY_KEY_E;
keydictionary["KEY_ACCEPT"] = KEY_NONCONVERT;
keydictionary["KEY_MODECHANGE"] = KEY_MODECHANGE;
keydictionary["KEY_SPACE"] = KEY_SPACE;
keydictionary["KEY_PRIOR"] = KEY_PRIOR;
keydictionary["KEY_NEXT"] = KEY_NEXT;
keydictionary["KEY_END"] = KEY_END;
keydictionary["KEY_HOME"] = KEY_HOME;
keydictionary["KEY_LEFT"] = KEY_LEFT;
keydictionary["KEY_UP"] = KEY_UP;
keydictionary["KEY_RIGHT"] = KEY_RIGHT;
keydictionary["KEY_DOWN"] = KEY_DOWN;
keydictionary["KEY_SELECT"] = KEY_SELECT;
keydictionary["KEY_PRINT"] = KEY_PRINT;
keydictionary["KEY_EXECUT"] = KEY_EXECUT;
keydictionary["KEY_SNAPSHOT"] = KEY_SNAPSHOT;
keydictionary["KEY_INSERT"] = KEY_INSERT;
keydictionary["KEY_DELETE"] = KEY_DELETE;
keydictionary["KEY_HELP"] = KEY_HELP;
keydictionary["KEY_KEY_0"] = KEY_KEY_0;

keydictionary["KEY_KEY_1"] = KEY_KEY_1;
keydictionary["KEY_KEY_2"] = KEY_KEY_2;
keydictionary["KEY_KEY_3"] = KEY_KEY_3;
keydictionary["KEY_KEY_4"] = KEY_KEY_4;
keydictionary["KEY_KEY_5"] = KEY_KEY_5;
keydictionary["KEY_KEY_6"] = KEY_KEY_6;
keydictionary["KEY_KEY_7"] = KEY_KEY_7;
keydictionary["KEY_KEY_8"] = KEY_KEY_8;
keydictionary["KEY_KEY_9"] = KEY_KEY_9;
//keydictionary["KEY_KEY_10"] = KEY_KEY_10;
keydictionary["KEY_KEY_A"] = KEY_KEY_A;
keydictionary["KEY_KEY_B"] = KEY_KEY_B;
keydictionary["KEY_KEY_C"] = KEY_KEY_C;
keydictionary["KEY_KEY_D"] = KEY_KEY_D;
keydictionary["KEY_KEY_E"] = KEY_KEY_E;
keydictionary["KEY_KEY_F"] = KEY_KEY_F;
keydictionary["KEY_KEY_G"] = KEY_KEY_G;
keydictionary["KEY_KEY_H"] = KEY_KEY_H;
keydictionary["KEY_KEY_I"] = KEY_KEY_I;
keydictionary["KEY_KEY_J"] = KEY_KEY_J;
keydictionary["KEY_KEY_K"] = KEY_KEY_K;
keydictionary["KEY_KEY_L"] = KEY_KEY_L;
keydictionary["KEY_KEY_M"] = KEY_KEY_M;
keydictionary["KEY_KEY_N"] = KEY_KEY_N;
keydictionary["KEY_KEY_O"] = KEY_KEY_O;
keydictionary["KEY_KEY_P"] = KEY_KEY_P;
keydictionary["KEY_KEY_Q"] = KEY_KEY_Q;
keydictionary["KEY_KEY_R"] = KEY_KEY_R;
keydictionary["KEY_KEY_S"] = KEY_KEY_S;
keydictionary["KEY_KEY_T"] = KEY_KEY_T;
keydictionary["KEY_KEY_U"] = KEY_KEY_U;
keydictionary["KEY_KEY_V"] = KEY_KEY_V;
keydictionary["KEY_KEY_W"] = KEY_KEY_W;
keydictionary["KEY_KEY_X"] = KEY_KEY_X;
keydictionary["KEY_KEY_Y"] = KEY_KEY_Y;
keydictionary["KEY_KEY_Z"] = KEY_KEY_Z;


keydictionary["KEY_LWIN"] = KEY_LWIN;
keydictionary["KEY_RWIN"] = KEY_RWIN;
keydictionary["KEY_APPS"] = KEY_APPS;
keydictionary["KEY_SLEEP"] = KEY_SLEEP;
keydictionary["KEY_NUMPAD0"] = KEY_NUMPAD0;
keydictionary["KEY_NUMPAD1"] = KEY_NUMPAD1;
keydictionary["KEY_NUMPAD2"] = KEY_NUMPAD2;
keydictionary["KEY_NUMPAD3"] = KEY_NUMPAD3;
keydictionary["KEY_NUMPAD4"] = KEY_NUMPAD4;
keydictionary["KEY_NUMPAD5"] = KEY_NUMPAD5;
keydictionary["KEY_NUMPAD6"] = KEY_NUMPAD6;
keydictionary["KEY_NUMPAD7"] = KEY_NUMPAD7;
keydictionary["KEY_NUMPAD3"] = KEY_NUMPAD8;
keydictionary["KEY_NUMPAD4"] = KEY_NUMPAD9;
keydictionary["KEY_LWIN"] = KEY_LWIN;
keydictionary["KEY_RWIN"] = KEY_RWIN;
keydictionary["KEY_APPS"] = KEY_APPS;
keydictionary["KEY_SLEEP"] = KEY_SLEEP;
keydictionary["KEY_MULTIPLY"] = KEY_MULTIPLY;
//keydictionary["KEY_ADKEY_KEY_ED"] = KEY_ADKEY_KEY_ED;
keydictionary["KEY_SEPARATOR"] = KEY_SEPARATOR;
keydictionary["KEY_SUBTRACT"] = KEY_SUBTRACT;
keydictionary["KEY_DECIMAL"] = KEY_DECIMAL;
keydictionary["KEY_DIVIDE"] = KEY_DIVIDE;
keydictionary["KEY_F1"] = KEY_F1;
keydictionary["KEY_F2"] = KEY_F2;
keydictionary["KEY_F3"] = KEY_F3;
keydictionary["KEY_F4"] = KEY_F4;
keydictionary["KEY_F5"] = KEY_F5;
keydictionary["KEY_F6"] = KEY_F6;
keydictionary["KEY_F7"] = KEY_F7;
keydictionary["KEY_F8"] = KEY_F8;
keydictionary["KEY_F9"] = KEY_F9;
keydictionary["KEY_F10"] = KEY_F10;
keydictionary["KEY_F11"] = KEY_F11;
keydictionary["KEY_F12"] = KEY_F12;
//keydictionary["KEY_F13"] = KEY_F13;
//keydictionary["KEY_F14"] = KEY_F14;
//keydictionary["KEY_F15"] = KEY_F15;
//keydictionary["KEY_F16"] = KEY_F16;
//keydictionary["KEY_F17"] = KEY_F17;
//keydictionary["KEY_F18"] = KEY_F18;
//keydictionary["KEY_F19"] = KEY_F19;
//keydictionary["KEY_F20"] = KEY_F20;
//keydictionary["KEY_F21"] = KEY_F21;
//keydictionary["KEY_F22"] = KEY_F22;
//keydictionary["KEY_F23"] = KEY_F23;
//keydictionary["KEY_F24"] = KEY_F24;

keydictionary["KEY_NUMLOCK"] = KEY_NUMLOCK;
keydictionary["KEY_SCROLL"] = KEY_SCROLL;
keydictionary["KEY_LSHIFT"] = KEY_LSHIFT;
keydictionary["KEY_RSHIFT"] = KEY_RSHIFT;
keydictionary["KEY_LCONTROL"] = KEY_LCONTROL;
keydictionary["KEY_RCONTROL"] = KEY_RCONTROL;
keydictionary["KEY_LMENU"] = KEY_LMENU;
keydictionary["KEY_RMENU"] = KEY_RMENU;
keydictionary["KEY_OEM_1"] = KEY_OEM_1;
keydictionary["KEY_PLUS"] = KEY_PLUS;
keydictionary["KEY_COMMA"] = KEY_COMMA;
keydictionary["KEY_MINUS"] = KEY_MINUS;
keydictionary["KEY_PERIOD"] = KEY_PERIOD;
keydictionary["KEY_OEM_2"] = KEY_OEM_2;
keydictionary["KEY_OEM_3"] = KEY_OEM_3;
keydictionary["KEY_OEM_4"] = KEY_OEM_4;
keydictionary["KEY_OEM_5"] = KEY_OEM_5;
keydictionary["KEY_OEM_6"] = KEY_OEM_6;
keydictionary["KEY_OEM_7"] = KEY_OEM_7;
keydictionary["KEY_OEM_8"] = KEY_OEM_8;
keydictionary["KEY_OEM_AX"] = KEY_OEM_AX;
keydictionary["KEY_OEM_102"] = KEY_OEM_102;
keydictionary["KEY_ATTN"] = KEY_ATTN;
keydictionary["KEY_CRSEL"] = KEY_CRSEL;
keydictionary["KEY_EXSEL"] = KEY_EXSEL;
keydictionary["KEY_EREOF"] = KEY_EREOF;
keydictionary["KEY_PLAY"] = KEY_PLAY;
keydictionary["KEY_ZOOM"] = KEY_ZOOM;
keydictionary["KEY_PA1"] = KEY_PA1;
keydictionary["KEY_OEM_CLEAR"] = KEY_OEM_CLEAR;
keydictionary["KEY_KEY_CODES_COUNT"] = KEY_KEY_CODES_COUNT;

}


void Python::registerIrrDevice(Luna *luna1,IrrlichtDevice &Device,InGameEventReceiver event){
    luna = luna1;
    device = &Device;
    driver = device->getVideoDriver();
    smgr   = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    mEvent = event;

    //camera = smgr->addCameraSceneNodeFPS(0, 100, .050f, -1, luna->keyMap, 8);
    //camera = smgr->addCameraSceneNode();

    //camera->setFarValue(10000);
    //camera = smgr->addCameraSceneNodeFPS();
    //camera->setFOV(PI/2);

    m_cScene = new Scene();
    m_cScene->registerIrrDevice(*device);
  //  m_cScene->setupLights();//Scene, setup for lights.
    int lastFPS = -1;
    u32 timeStamp = device-> getTimer()-> getRealTime(),deltaTime = 0;
    device->setEventReceiver ( &mEvent);
//    device->getCursorControl()->setVisible(false);
#ifdef FPS
    Elevator::Instance()->Instance();
    ///Player::Instance()->Instance();//obsolete
    //    Collision::Instance()->Instance();
    ///Player::Instance()->setDevice(device); //obsolete
    //   Collision::Instance()->setDevice(device);
#endif
//scene::IAnimatedMesh *mesh = (IAnimatedMesh*) smgr->getMesh("media/player/player.x");
//scene::IAnimatedMeshSceneNode *skelNode = (IAnimatedMeshSceneNode*) smgr->addAnimatedMeshSceneNode(mesh);
//cSkeleton skeleton; // moved externally
//skeleton.Initialize(skelNode, 8);
//core::vector3df pos = skeleton.getSkeletonSceneNode()->getPosition();
//skelNode->addShadowVolumeSceneNode();
//smgr->setShadowColor(video::SColor(150,0,0,0));
//smgr->addLightSceneNode(0, core::vector3df(0,0,0),video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 600.0f);


#ifdef PostProcess  // tried to put into scripting system but it needs to be worked on more still
#define GL_OLDMONITOR "uniform float randNum,time,v0;uniform sampler2D texture1;float rand(in float s){return sin(gl_TexCoord[0].x*(1009.0+s*10.0)+tan(gl_TexCoord[0].y*(1090.0+s*100.0)+tan(gl_TexCoord[0].x*111.0+s*10000.0))+s*4.0+gl_TexCoord[0].y*10000.0)*0.5+0.5;}float tear(in float y){return (y-0.8)*0.01/(y*y*y*y+2.0);}void main(void){float c=dot(texture2D(texture1,vec2(floor(gl_TexCoord[0].x*500.0)*0.002+tear((gl_TexCoord[0].y-1.2+mod(time*0.1,1.4))*50.0)*rand(randNum)*5.0*v0,floor(gl_TexCoord[0].y*200.0)*0.005+floor(fract(time*0.1+randNum*0.1)*1.1)*0.03*v0)),vec4(0.2,0.5,0.3,0.0));gl_FragColor=(texture2D(texture1,vec2(gl_TexCoord[0].x+tear(tan(gl_TexCoord[0].y*10.0+time*2.0))*v0,gl_TexCoord[0].y))*(1.0-0.7*v0)+c*0.7*v0+vec4(rand(randNum))*0.1*v0)*(1.0-(sin(gl_TexCoord[0].y*400.0)*0.05+(pow(abs(gl_TexCoord[0].x*2.0-1.0),4.0)+pow(abs(gl_TexCoord[0].y*2.0-1.0),4.0))*0.5)*v0);}"
#define DX_OLDMONITOR "sampler2D s;float randNum,time,v0;float rand(in float2 t,in float s){return frac(t.x*(1009.0+s*10.0)+tan(t.y*(1090.0+s*100.0)+t.x*111.0)+t.y*10000.0)-0.5;}float tear(in float y){return (y-0.8)*0.01/(y*y*y*y+2.0);}float4 main(float2 t:TEXCOORD0):COLOR{float c=dot(tex2D(s,float2(t.x+tear(frac(t.y-time*0.2)*70.0-35.0)*(rand(t,randNum)+0.5)*4.0,floor(t.y*200.0)*0.005)),float4(0.2,0.5,0.3,0.0));return tex2D(s,t)*(1.0-0.7*v0)+(c*0.7+float4(0.1,0.1,0.1,0.0)*rand(t,randNum))*(1.0-sin(t.y*400.0)*0.05-(pow(abs(t.x-0.5),4.0)+pow(abs(t.y-0.5),4.0))*8.0)*v0;}"

// This monitor effect is NOT supported, and has been known to have problems. I encourage you to use the officially supported PP_MONITOR effect instead in your programs.

// A much simpler shader; this will add a constant number (set by parameters) to the rgba channels
#define GL_A_SIMPLER_SHADER "uniform float v0;uniform sampler2D texture1;void main(void){gl_FragColor=texture2D(texture1,gl_TexCoord[0].xy)+v0;}"
#define DX_A_SIMPLER_SHADER "sampler2D s;float v0;float4 main(float2 t:TEXCOORD0):COLOR{return tex2D(s,t)+v0;}"

	//PostProcessing
    IPostProc* ppRenderer = new CRendererPostProc( smgr, dimension2du( 1024, 512 ),
                                                    true, true, SColor( 255u, 100u, 101u, 140u ) );
    ppBlurDOF   = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), PP_BLURDOF );
    ppBlur          = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), PP_BLUR, 0.00081f );
	CEffectPostProc* ppInvert = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), PP_INVERT );
	CEffectPostProc* ppBlur = new CEffectPostProc( ppInvert, dimension2du( 1024, 512 ), PP_BLUR, 0.01f );
	ppMine = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), GL_OLDMONITOR, DX_OLDMONITOR, EPST_PS_1_2, EPST_PS_2_0, EMT_SOLID, PPF_FROMCODE, 1.0f );

    ppBlur->setQuality( PPQ_GOOD );
    ppMine->setRequiredVariables( 1, true, true ); // (number of input parameters, uses time?, uses randNum?)

    ppMine->setTimer( device->getTimer( ) );

    //bPProcess=1;
#endif

    //skin = guienv->getSkin();
#ifdef BOX2DLITE
    InitDemo(0); //
#endif
initkeys();
}

#include "PyScene.h"
// make a post draw loop instead of putting things into the checkkey
PyObject * Python::PyIrr_exec(PyObject * self,PyObject * args){ //active camera
char * script;
char * arg;
    PyArg_ParseTuple(args,"ss",&script,&arg);
//sts = system(command);s
//popen("wget http://google.com", "w");
}

PyObject * Python::PyIrr_GetString(PyObject * self,PyObject * args){ //active camera
    char * arg;
    PyArg_ParseTuple(args,"s",&arg);

    //returnString=arg;
    returnString="../media/frogger.pys";
    //string tester = "../media/" + arg + "frogger.pys";
    luna->pyloader="../media/frogger.pys";
    //luna->pyloader="../media/" + tester + "frogger.pys";
    Python::returnString=arg;

    //returnString=arg;
    //printf(returnString);
    //std::cout <<"setting game loader";
    //printf("%s",returnString);
    //printf("setting game loader");

    return Py_BuildValue("s",arg);
}

PyObject * Python::PyIrr_using(PyObject * self,PyObject * args){
    //ExecuteScript(irr::core::string<char> scriptname){
    char * script;
    char * arg;
    PyArg_ParseTuple(args,"ss",&script,&arg);
    ExecuteScript(script);

    return Py_BuildValue("");
}

PyObject * Python::PyIrr_Delay(PyObject * self,PyObject * args){ //PyIrr_Delay
    //repurpose this for a path move delay
    float delay;
    PyArg_ParseTuple(args,"f",&delay);
 //   device->sleep(delay);
    usleep(delay);
    return Py_BuildValue("");
}

PyObject * Python::PyIrr_Sleep(PyObject * self,PyObject * args){
    int ammount;
    PyArg_ParseTuple(args,"i",&ammount);
    usleep(ammount);
    //device->sleep(ammount);
    return Py_BuildValue("");
}

PyObject * Python::PyIrr_setTime(PyObject * self,PyObject * args){
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



PyObject * Python::PyIrr_WayPoint(PyObject * self,PyObject * args){
 //add //remove // check // load // clear
 // could have python scripted waypoint manager too
irr::core::array<ISceneNode*> waypoints;

//if(waypoints.size() > 0)
//{
//    for(u32 i = 0; i < waypoints.size()-1; i++)
//    {
//      waypoints[i]->remove();
//      waypoints.erase(i);
//    }
//    waypoints.clear();
//}

 //checking distance from node to waypoints
 // playerPos = cam->getPosition(); or node position
//  for(u32 i = 0; i < waypoints.size(); i++)
//  {
//    if(waypoints[i]->getPosition().getDistanceFrom(playerPos) < 50.0f)
//    {
//
//
//    }

//      if(particleNodeArray.size() > 0)
//  {
//    for(u32 i = 0; i < particleNodeArray.size()-1; i++)
//    {
//      particleNodeArray[i]->drop();
//      particleNodeArray.erase(i);
//    }
//    particleNodeArray.clear();
//  }

 // }

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

    return Py_BuildValue("");
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
#include "../Scripting/pyFileIO.h"
#include "PyMath.h"
#include "PySound.h"
#include "PyCamera.h"
#include "PyInput.h"
#include "PyGUI.h"

#include "../Scene/RainMan.h"

#endif

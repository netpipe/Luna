 #ifndef INCLUDES
 #define INCLUDES
#define MINIMAL
 #ifndef MINIMAL

 //#define PYTHON  // defined in the codeblocks project option defines for target management and testing builds

 #define COMPRESS //needed for empython


 #ifndef __EMSCRIPTEN__
 //#define SOUND
 //#define VIDEO

 //todo put in simple openal sound
 #endif

//for AgAudio

//#define AgAudio // not working with emscripten
//#ifdef __EMSCRIPTEN__
#ifdef AgAudio
  #define _DEBUG_MODE_
  #define _PLAY_SOUND_
#endif

//#define SDLMixer // wip - might not be compatable with the engine
//#define OPENAL2 // working with emscripten
//#define SDLSound //- seems to play and freeze needs threading


  //  #define IRRCD   // irrlicht Collision Detection
    #define EVENTS
    #define FPS
    #define CSG // constructive solid geometry
    #define SGRAPH2D // 2d plot graph
    #define WIND
    #define SCENE
   // #define IRRc
   //PathFinding
    #define RECAST
    #define MINAV
    #define OPENSTEER

  #define WATER
  //  #define ReflectiveWater
  //  #define RealisticWater

  #define SPARK
  //#define BOX2D  // needs to be implimented properly still
 // #define SKELETON // needs to be updated
  #define PostProcess
//  #define VEGETATION //grass,weeds, vines
//  #define TREES //very cpu intensive does not work with emscripten yet.
  #define ATMOSPHERE  //  freezes when no video acceleration is used
                        //  or as a user without access to video rights is used
  #define FLARE
  //#define FLARES
  //#define FLARE2  // more realistic and working
  //#define FLUIDSYNTH

  //#define DECALS       //not used
  #define DECALS2
  #define TESSELATE

  //  #define CODEEDITOR
  //#define FLAG    //
  //#define FLAG2   //FMX
  //#define COMPASS
  #define BOIDS
  #define TERRAIN
  //  #define occlusion.
  #define OCCLUSION
  //  #define FPSWEAPON // no uses diff event receiver than player so wont drive car or shoot cubes // screws with the flare2

  #define PHYSICS
  #ifdef PHYSICS
  //if bullet carnot enabled with physics and car calls it crashes FIXME
  #define BULLETCAR // if FPSWEAPON is enabled the car wont work. diff event rec
  #define LOADLEVELS // with occlusion its slow?
  #define BULLETBLEND
  #define RAGDOLL   //bulletRagdoll
  #endif


  #define EXTRAS
  //  #define DESTRUCTION //not working
  #define FORMATIONDEMO
  #define HUD
  #define Image2D // Just testing out
  #define CHOPPER

  #define SQLITE

  #define SCALC
  #define FT2
  #define SPRITES
#else // MINIMAL defines
    #define EVENTS
    #define FPS
        #define CSG // constructive solid geometry
    #define SGRAPH2D // 2d plot graph
    #define WIND
    #define SCENE
    #define PHYSICS
    #define FPS
#endif

//#define PYTHON_MINIMALTEST

  #endif

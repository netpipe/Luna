 #ifndef INCLUDES
 #define INCLUDES
 //#define PYTHON  // defined in the codeblocks project option defines for target management and testing builds

 #define COMPRESS //needed for empython


 #ifndef __EMSCRIPTEN__
 //#define SOUND
 //todo put in simple openal sound
 #endif

//for AgAudio
#define _DEBUG_MODE_
#define _PLAY_SOUND_
#define AgAudio // not working with emscripten
//#define SDLMixer // wip
//#define OPENAL // working with emscripten
//#define SDLSound


   // #define IRRCD   // irrlicht Collision Detection
    #define EVENTS
  //  #define FPS
   // #define CSG // constructive solid geometry
   // #define SGRAPH2D // 2d plot graph
    //#define WIND
    #define SCENE
   // #define IRRc
  //  #define PostProcess
  #define WATER
  //  #define ReflectiveWater
  //  #define RealisticWater

  #define SPARK
  //#define BOX2D  // needs to be implimented properly still
 // #define SKELETON // needs to be updated
  //#define PostProcess
  //#define VEGETATION
 // #define TREES //very cpu intensive does not work with emscripten yet.
  #define ATMOSPHERE  //  freezes when no video acceleration is used
                        //  or as a user without access to video rights is used
  #define FLARE
  //#define FLARES
  //#define FLARE2  // more realistic and working

  #define DECALS       //decalmanager sortof working slow tho
  //#define DECALS2       // simple decals
  #define TESSELATE

  //  #define CODEEDITOR
  //#define FLAG    //
  //  #define FLAG2   //FMX
   // #define COMPASS
  //#define BOIDS
  #define TERRAIN
  //  #define occlusion.
//#define OCCLUSION
  //  #define FPSWEAPON // no uses diff event receiver than player so wont drive car or shoot cubes // screws with the flare2
  #define PHYSICS
  //if bullet carnot enabled with physics and car calls it crashes FIXME
  #define BULLETCAR // if FPSWEAPON is enabled the car wont work. diff event rec
  #define LOADLEVELS // dont use this without bullet or with occlusion its slow?
  //  #define BULLETBLEND
  //  #define RAG   //bulletRagdoll
  #define EXTRAS
  //  #define DESTRUCTION //not working
  #define FORMATIONDEMO
  #define HUD
  #define Image2D // Just testing out
  #define CHOPPER
  #define OPENSTEER
  #define SQLITE

//  #define SCALC
//#define FT2
//#define SPRITES
//#define PYTHON_MINIMALTEST
//    #define VIDEO

  #endif

//#define NDEBUG // for testing networking
#ifdef EXTRACOMPILE  //leftovers and extra from minimal
 #define MINIMAL2
 //#define COMPRESS //needed for empython
//#define SDLMixer // wip - might not be compatable with the engine
//#define OPENAL2 // working with emscripten
//#define SDLSound //- seems to play and freeze needs threading
    // #define WII
   // #define IRRc
   //PathFinding
    #define RECAST
    #define MINAV
    #define OPENSTEER
    #define SPARK
    #define SOUND

    #ifdef NDEBUG
      #define NETWORK
    #endif
 // #define SKELETON // needs to be updated
//  #define VEGETATION //grass,weeds, vines
 // #define FLARE
  //#define FLARES
  //#define FLARE2  // more realistic and working
  #define FLUIDLITE
  //#define FLUIDSYNTH //has been replaced by fluidlite
  //#define DECALS       //not used
//  #define DECALS2
  #define TESSELATE
  //  #define occlusion.
  //  #define FPSWEAPON // no uses diff event receiver than player so wont drive car or shoot cubes // screws with the flare2
      #define RIBBONTRAIL
  //  #define DESTRUCTION //not working
  #define FORMATIONDEMO
 // #define HUD //causes crashing
 // #define FT2
#endif


#ifdef MINIMAL
 // MINIMAL defines
    #define EVENTS
    #define FPS
    #define CSG // constructive solid geometry
    #define SGRAPH2D // 2d plot graph
    #define WIND
    #define SCENE
  //  #define PHYSICS
    #define FPS
    #define PYTHON
   // #define ANGELSCRIPT
    #define Image2D
    #define IRRCD
    #define OCCLUSION
        #define WATER //enables the other 2
       // #define ReflectiveWater
        #define RealisticWater //cannot be enabled with postprocessing
    #define EXTRAS
    #define CHOPPER
    #define BOIDS
    #define TERRAIN
    #define VEGETATION //grass,weeds, vines
    #define FLAG
    #define FLAG2      //FMX
    //#define WII //not ready for use yet also requires libudev.
                    //xwiimote is easier to use with suse linux
                    //cwiid has balanceboard support

    #define COMPASS
    #define TESSELATE
    #define SCALC
    #define SPRITES
    //#define SKELETON  // needs to be updated
    #define PostProcess

    #define TREES       //very cpu intensive does not work with emscripten yet.
    #define forest
    #define ATMOSPHERE  //  freezes when no video acceleration is used
                        //  or as a user without access to video rights is used
    #define RIBBONTRAIL
    #define BOX2DLITE
      //#define FLARE
      //#define DECALS2 //replace needing physics to get working
     // #define SQLITE
    #define LOADLEVELS

    #ifdef MINIMAL2 //not so minimal extras
        //#define BOX2D // engine uses box2dlite already this is for testing

        //#define SDLMixer // wip - might not be compatable with the engine
        //#define OPENAL2 // working with emscripten
        //#define SDLSound //- seems to play and freeze needs threading
        //#define SQLITE
       // #define AgAudio
            #ifdef AgAudio
                #define _DEBUG_MODE_
                #define _PLAY_SOUND_
            #endif
         //   #define SOUND
        //#define SDLSound
        //#define FLUIDLITE

        #define CODEEDITOR

        //#define OPENAL2
        #define _IRR_COMPILE_WITH_BSP_LOADER_
        //#define OIS2
        //#define OIS2_LINUX_JOY_DEBUG
        //#define TILED2D
        //#define PYTHON_MINIMALTEST
       // #define PHYSICS // custom BulletImplimentation
        //#define IRRBULLET
        #endif

  #ifdef PHYSICS
  //if bullet carnot enabled with physics and car calls it crashes FIXME
  #define BULLETCAR // if FPSWEAPON is enabled the car wont work. diff event rec
  #define LOADLEVELS // with occlusion its slow?
 // #define BULLETBLEND
  #define RAGDOLL   //bulletRagdoll
  #endif

//  #define POLYVOX

#else  // mainly used for old stuff before cleanup , emscripten perhaps it should work with minimal too

 #define PYTHON  // defined in the codeblocks project option defines for target management and testing builds
 // #define ANGELSCRIPT
 #define COMPRESS //needed for empython


 #ifndef __EMSCRIPTEN__
 #define SOUND
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



    // #define WII
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
  //#define FLUIDLITE
  //#define FLUIDSYNTH //has been replaced by fluidlite

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

  #define BOX2DLITE
  //#define PHYSICS
  #ifdef PHYSICS
  //if bullet carnot enabled with physics and car calls it crashes FIXME
  #define BULLETCAR // if FPSWEAPON is enabled the car wont work. diff event rec
  #define LOADLEVELS // with occlusion its slow?
 // #define BULLETBLEND
  #define RAGDOLL   //bulletRagdoll
  #endif


  #define EXTRAS
      #define RIBBONTRAIL
  //  #define DESTRUCTION //not working
  #define FORMATIONDEMO
 // #define HUD
  #define Image2D // Just testing out
  #define CHOPPER

  #define SQLITE
  #define SCALC
  #define FT2
  #define SPRITES

  //#define PYTHON_MINIMALTEST

#endif

#ifndef Luna_H
#define Luna_H

#include <unistd.h>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "config.h"  // has the defines in it for compile
//#include <pthread.h>

#include "Events/Events.h"
#include "Events/InGameEventReceiver.h"
#include "Scene/customNodes.h"

#ifdef SOUND
	#include <cAudio.h>
#endif

#include "entities/player.h"
//#include "Encryption/Blowfish.h"

#ifdef IRRBULLET
    #include "Physics/irrBullet-0.1.9/include/irrBullet.h"
#endif

#ifdef PHYSICS
	#include "Physics/Physics.h"
	#include "Physics/Vehicle.h"
#endif

	#include "Scene/Scene.h"

#ifdef DECALS2
	#include "./Scene/decals/decalscenenode.h"
#endif

#ifdef TERRAIN
	#include "TerrainFactory/Terrain.h"
#endif

#ifdef NETWORK
	#include <irrNet.h>
	//#include "Net/irrNetClient.h"
#endif

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
	#include <libtar.h>
#endif

#ifdef AgAudio
	#include "./Input/AgAudio/Sound.h"
#endif


#ifdef CODEEDITOR
    #include "GUI/CodeEditor/CGUIEditBoxIRB.h"
#endif // CODEEDITOR


//#include "TerrainFactory/GrassSceneNode/CGrassPatchSceneNode.h"
//#include "Input/Model/IrrAssimp/IrrAssimp.h"

class Luna
{
	public:

	Luna ( int argc, char** argv );
	~Luna(); // Cleans up the engine

		int Run();
		IrrlichtDevice *device;
		unsigned int resolution[2];
        IVideoDriver *driver;
		ISceneManager *smgr;
		char * pyloader="../media/gameloader.pys";

		int init();
		int shutdown();
		int lobby();
		int mainloop();
		int devloop();
		int doLogin ( const std::wstring &username, const std::wstring &password );
		int handleMessages();
		void rendermain();
		void main_loop();
		bool iinit=false;
		   u32 then ;
		int lastFPS;
		bool bshutdown=false;
		int countr;
		//char * returnString="../media/gameloader.pys";

//		#ifdef AgAudio
////		Sound *m_sound;
//     		Sound *m_sound;
//     		Sound m_default_sound_buffer;
//		#endif

//    		void sound_loop_then_quit();
//		int SDLPlay();

		int AddShader();

        void CheckKeyStates(void);

		IGUIEnvironment *guienv;

		#ifdef EVENTS
            EventRec events;
            InGameEventReceiver m_cInGameEvents;
		#endif
        // Factory threads
		//pthread_t soundThread

        //AUDIO--------------------------
        #ifdef SOUND
			cAudio::IAudioManager* manager;
			cAudio::IAudioSource* mysound;
		#endif

		#include "./Input/SDLMixer.h"

		// Encryption--------------------
		//Encryption::Blowfish enc;
		// Network related
       // net::SOutPacket packet;

        // Character related
		std::wstring username;
		std::wstring password;

		#ifdef FPS
		// Player Physics---------------
			Player *m_cPlayer;
        #endif

        //  Scene *m_cScene;
        #ifdef PHYSICS
		Physics *m_cPhysics;
		#endif
        SKeyMap keyMap[8]; // KEYMAP
        f32 frameDeltaTime;

        //video::ITexture *tex1;
        //video::ITexture *tex2;
        //    scene::CGrassPatchSceneNode *grass[100];
        //core::array<video::E_MATERIAL_TYPE> modes;
        //
        //scene::IWindGenerator *wind;

    int MakeTrees();
    void recursiveFillMetaSelector(scene::ISceneNode* node, scene::IMetaTriangleSelector* meta );

    scene::IMetaTriangleSelector* metaSelector;
	scene::ISceneNodeAnimatorCollisionResponse* anim;
  //      ICameraSceneNode* camera;

	struct SAppContext
	{
		IrrlichtDevice *device;
		s32				counter;
		IGUIListBox*	listbox;
	};

    #ifdef CODEEDITOR
	CGUIEditBoxIRB * codeEditor;
	IGUIContextMenu * menu;
#endif
		IGUIWindow* windows;
	private:

	protected:
};




#endif

#ifndef _Sound_HPP_
#define _Sound_HPP_
#include "../../config.h"
#ifdef AgAudio
//#include "../../Luna.h"
#include "audio.h"

#define _DEBUG_MODE_
#define _PLAY_SOUND_
//#include "Sound.hpp"

class Sound
{

  public:
    unsigned int
      *musicMenu,
      *musicStage1,
      *musicStage2,
      *musicStage3,
      *musicDead,
      *musicClear,

      *sampleCellPickup;

    float
      pos[3],
      samplePos[3],
      lastPos[3],
      vel[3];

//    vector3df rot;

	pthread_t soundThread;
	agEngine::AudioDevice *adevice;

		//! Sound Init
//	agEngine::SoundData *deadS;
	agEngine::SoundData *menuM;
//	agEngine::SoundData *stage1M;
//	agEngine::SoundData *stage2M;
//	agEngine::SoundData *stage3M;
//	agEngine::SoundData *stage4M;
//	agEngine::SoundData *deadM;
//	agEngine::SoundData *clearM;
//	agEngine::SoundData *footS;

	agEngine::AudioSource *musicSource;
	// Add more channels if you want
	agEngine::AudioSource *channel1;
	agEngine::AudioSource *channel2;



    static Sound *Instance();

    void SetDefaultValues(void);
    void Close();
    int Create(void);
    void PlayBackgroundMusic(int music);
//    void PlayCellPickupSample(vector3df position);
//    void UpdateListener(vector3df position, vector3df rotation);
    void Drop(void);
    void PlayFootStepSound(bool);
    void PlayAll(void);

  protected:

    static Sound *m_sound;
    static Sound m_default_sound_buffer;
};

#endif
#endif

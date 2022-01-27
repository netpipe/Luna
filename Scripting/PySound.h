#include "../config.h"
#ifdef PYTHON
PyMethodDef irr_Sound[] =
{
    {"fluidlite",Python::PyIrr_FluidSynth,METH_VARARGS,"fluidsynth"},
    {"soundman",Python::PyIrr_SoundMan,METH_VARARGS,"PyIrr_SoundMan"},
	{NULL,NULL,0,NULL}
};


//    static Sound *m_sound2;
  //  static Sound m_default_sound_buffer;

PyObject * Python::PyIrr_SoundMan(PyObject * self,PyObject * args){ //active camera

    int param,state;
    char * sound;

    PyArg_ParseTuple(args,"isi",&param,&sound,&state);

    #ifdef SOUND


    // sound intensity for raycasted sound.  // surfaceRoughnessHardness/propigation factor, distance,handle
    switch (param){

    case 0:
      {
           //   managerID->initialize(1);
       // mysound=stoi(sound);
      //      mysound = managerID->create("bling","./media/bling.ogg",false);
      //   luna->manager->initialize(luna->manager->getAvailableDeviceName(0));
      //managerID->initialize(1);
           mysound = managerID->create(sound,sound,false);
    //        return Py_BuildValue("l",manager
        //    mysound->play2d(true);
          return Py_BuildValue("l",mysound);
      }
      break;
    case 1:
      {
//        managerID = cAudio::createAudioManager(true);  // broken has to be done from main
      if (state){ // play sound
       long mysound2=std::atoi(sound);
       mysound=mysound2;

       if( managerID) // nonzero to show initialized
        {
          mysound->play2d(true);
        }

      }else{ // stop sound
            mysound->stop();
      }

     //        return Py_BuildValue("l",managerID);
       return Py_BuildValue("l",managerID);
        //break;
      }

        break;

//    case 2: //
//      {
////            mysound->stop();
//      }
    //  break;
    }
    return Py_BuildValue("l",managerID);
  #endif


  #ifdef AgAudio
    switch (param){
          case 0:
      {
//        luna->m_sound->Create();
          Sound::m_sound->Create();
      }break;
    case 1:
      {
      //  	luna->m_sound->Create();
      //luna->m_sound->Instance()->PlayAll();
      //	luna->m_sound->PlayBackgroundMusic(1);
      Sound::m_sound->PlayBackgroundMusic(1);

      }break;
    }
#endif
//m_sound2 = luna->m_sound;
//luna->m_sound->PlayBackgroundMusic(1);

#ifdef OPENAL
    //switch (param){
    //case 0:
#endif

#ifdef SDLSOUND
    //switch (param){
    //case 0:
#endif

return Py_BuildValue("");
}
#ifdef FLUIDLITE
#include "../Input/FluidLite/include/fluidlite.h"
#define SAMPLE_RATE 44100
#define SAMPLE_SIZE 2 //4: Float Buffer   2: Signed Int Buffer
#define NUM_FRAMES SAMPLE_RATE
#define NUM_CHANNELS 2
#define NUM_SAMPLES (NUM_FRAMES * NUM_CHANNELS)
#define TIME_INTERVAL 1000000 //1500000:duration
#endif
PyObject * Python::PyIrr_FluidSynth(PyObject * self,PyObject * args){ //active camera
#ifdef FLUIDLITE
//http://www.fluidsynth.org/api/index.html#MIDIPlayerMem
    int typee;
    char * sound;
    char * param;
    PyArg_ParseTuple(args,"ssi",&sound,&param,&typee);
//#define NETWORK_SUPPORT


//if (param == "init"){
	fluid_settings_t* settings = new_fluid_settings();
	fluid_synth_t* synth = new_fluid_synth(settings);
	int res = fluid_synth_sfload(synth, "../media/soundfont.sf2", 1);

	double dlength = (double)(SAMPLE_RATE * NUM_CHANNELS * SAMPLE_SIZE) * TIME_INTERVAL / 1000000;
	long length = (long)dlength;
	char* audio_buf = (char*)calloc(1, length);
//}

switch (typee){
case 0:{
            int nKey = 60 + rand() % 30;
			fluid_synth_noteon(synth, 0, nKey, 127);
			fluid_synth_write_s16(synth, SAMPLE_RATE, audio_buf, 0, NUM_CHANNELS, audio_buf, 1, NUM_CHANNELS);
			fluid_synth_noteoff(synth, 0, 60);

			//Create a IAudio object and load a sound from a file
			//cAudio::IAudioSource* mysound = audioMgr->create("bling", "ec7_stereo.ogg", true);
			mysound = managerID->createFromRaw(
				"bling", audio_buf, length, SAMPLE_RATE, cAudio::EAF_16BIT_STEREO);

			//Set the IAudio Sound to play3d and loop
			//play3d takes 4 arguments play3d(toloop,x,y,z,strength)
		//	if (mysound && listener)
		//	{
//				listener->setPosition(cAudio::cVector3(0, 0, 0));
				mysound->play3d(cAudio::cVector3(0, 10, 0), 2.0f, true);
				mysound->setVolume(0.20f);
				mysound->setMinDistance(1.0f);
				mysound->setMaxAttenuationDistance(100.0f);

				//Play for 10 seconds
				const int ticksToPlay = 400;
				int currentTick = 0;
				int currentSecTick = 0;

			//	while (mysound->isPlaying() && currentTick < ticksToPlay)
			//	{
					//Figure out the location of our rotated sound
//					rot += 0.1f * 0.017453293f;  //0.1 degrees a frame

					//Sound "starts" at x=5, y=0, z=0
//					float x = 5.0f * cosf(rot) - 0.0f * sinf(rot);
		//			float z = 0.0f * cosf(rot) + 5.0f * sinf(rot);
		//			mysound->move(cAudio::cVector3(x, 0.0, z));

//					++currentTick;
//
//					if (currentTick / 1000 > currentSecTick)
//					{
//						++currentSecTick;
//						std::cout << ".";
//					}

					//Sleep for 1 ms to free some CPU
					//cAudio::cAudioSleep(1);
			//	}
			//}
			//audioMgr->releaseAllSources();
		//}

//		std::cout << std::endl;

		//cAudio::destroyAudioManager(audioMgr);
	//}
//	else
//	{
//		std::cout << "Failed to create audio playback manager. \n";
//	}

	//free(audio_buf);
return Py_BuildValue("l",mysound);
  //initFluidLite();
}break;

case 1:{
//playNote();
}break;
}

}
#else
return Py_BuildValue("");
}
#endif

#endif

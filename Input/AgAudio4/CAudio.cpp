#include "CAudio.h"

namespace agEngine
{
    namespace Audio
    {
        AudioDriver* AudioDriver::instance = NULL;

        const bool enableMp3Playback = true;

        /*
        	Main Audio Device
        */
        AudioDriver::AudioDriver()
        {
            // Zero out the refcount
            sourceCount = 0;
            usedEffectSlots = 0;
            usedEffects = 0;
            usedFilters = 0;

            // Initialize the OpenAL backend
            if ( ! ( soundDevice = alcOpenDevice ( NULL ) ) )
            {
                active = false;
            }
            else
            {
                active = true;

                // Check for effects extension
                effectsEnabled = (alcIsExtensionPresent(soundDevice, "ALC_EXT_EFX") == AL_TRUE);
                if (effectsEnabled)
                {
                    printf("effects enabled");
                    ALint attribs[4];
                    attribs[0] = ALC_MAX_AUXILIARY_SENDS;
                    attribs[1] = 4;
                    soundContext = alcCreateContext ( soundDevice, attribs );
                    alcMakeContextCurrent ( soundContext );

                    ALCint sends = 0;
                    alcGetIntegerv(soundDevice, ALC_MAX_AUXILIARY_SENDS, 1, &sends);

                    // Get the functions from the openAL dll.
                    alExt.alGenEffects = (LPALGENEFFECTS) alGetProcAddress("alGenEffects");
                    alExt.alDeleteEffects = (LPALDELETEEFFECTS) alGetProcAddress("alDeleteEffects");
                    alExt.alIsEffect = (LPALISEFFECT) alGetProcAddress("alIsEffect");
                    alExt.alEffecti = (LPALEFFECTI) alGetProcAddress("alEffecti");
                    alExt.alEffectiv = (LPALEFFECTIV) alGetProcAddress("alEffectiv");
                    alExt.alEffectf = (LPALEFFECTF) alGetProcAddress("alEffectf");
                    alExt.alEffectfv = (LPALEFFECTFV) alGetProcAddress("alEffectfv");
                    alExt.alGetEffecti = (LPALGETEFFECTI) alGetProcAddress("alGetEffecti");
                    alExt.alGetEffectiv = (LPALGETEFFECTIV) alGetProcAddress("alGetEffectiv");
                    alExt.alGetEffectf = (LPALGETEFFECTF) alGetProcAddress("alGeteffectf");
                    alExt.alGetEffectfv = (LPALGETEFFECTFV) alGetProcAddress("alGeteffectfv");

                    alExt.alGenFilters = (LPALGENFILTERS) alGetProcAddress("alGenFilters");
                    alExt.alDeleteFilters = (LPALDELETEFILTERS) alGetProcAddress("alDeleteFilters");
                    alExt.alIsFilter = (LPALISFILTER) alGetProcAddress("alIsFilter");
                    alExt.alFilteri = (LPALFILTERI) alGetProcAddress("alFilteri");
                    alExt.alFilteriv = (LPALFILTERIV) alGetProcAddress("alFilteriv");
                    alExt.alFilterf = (LPALFILTERF) alGetProcAddress("alFilterf");
                    alExt.alFilterfv = (LPALFILTERFV) alGetProcAddress("alFilterfv");
                    alExt.alGetFilteri = (LPALGETFILTERI) alGetProcAddress("alGetFilteri");
                    alExt.alGetFilteriv = (LPALGETFILTERIV) alGetProcAddress("alGetFilteriv");
                    alExt.alGetFilterf = (LPALGETFILTERF) alGetProcAddress("alGetFilterf");
                    alExt.alGetFilterfv = (LPALGETFILTERFV) alGetProcAddress("alGetFilterfv");

                    alExt.alGenAuxiliaryEffectSlots = (LPALGENAUXILIARYEFFECTSLOTS) alGetProcAddress("alGenAuxiliaryEffectSlots");
                    alExt.alDeleteAuxiliaryEffectSlots = (LPALDELETEAUXILIARYEFFECTSLOTS) alGetProcAddress("alDeleteAuxiliaryEffectSlots");
                    alExt.alIsAuxiliaryEffectSlot = (LPALISAUXILIARYEFFECTSLOT) alGetProcAddress("alIsAuxiliaryEffectSlot");
                    alExt.alAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI) alGetProcAddress("alAuxiliaryEffectSloti");
                    alExt.alAuxiliaryEffectSlotiv = (LPALAUXILIARYEFFECTSLOTIV) alGetProcAddress("alAuxiliaryEffectSlotiv");
                    alExt.alAuxiliaryEffectSlotf = (LPALAUXILIARYEFFECTSLOTF) alGetProcAddress("alAuxiliaryEffectSlotf");
                    alExt.alAuxiliaryEffectSlotfv = (LPALAUXILIARYEFFECTSLOTFV) alGetProcAddress("alAuxiliaryEffectSlotfv");
                    alExt.alGetAuxiliaryEffectSloti = (LPALGETAUXILIARYEFFECTSLOTI) alGetProcAddress("alGetAuxiliaryEffectSloti");
                    alExt.alGetAuxiliaryEffectSlotiv = (LPALGETAUXILIARYEFFECTSLOTIV) alGetProcAddress("alGetAuxiliaryEffectSlotiv");
                    alExt.alGetAuxiliaryEffectSlotf = (LPALGETAUXILIARYEFFECTSLOTF) alGetProcAddress("alGetAuxiliaryEffectSlotf");
                    alExt.alGetAuxiliaryEffectSlotfv = (LPALGETAUXILIARYEFFECTSLOTFV) alGetProcAddress("alGetAuxiliaryEffectSlotfv");

                    if (!alExt.alGenEffects || !alExt.alDeleteEffects || !alExt.alIsEffect)
                    {
                        effectsEnabled = false;
                         printf("effects false");
                    }
                    else
                    {
                        for (effectSlots = 0; effectSlots < 16; ++effectSlots)
                        {
                            alExt.alGenAuxiliaryEffectSlots(1, &effectSlot[effectSlots]);
                            if (alGetError() != AL_NO_ERROR)
                                break;
                        }

                        for (effects = 0; effects < 16; ++effects)
                        {
                            alExt.alGenEffects(1, &effect[effects]);
                            if (alGetError() != AL_NO_ERROR)
                                break;
                        }

                        for (filters = 0; filters < 16; ++filters)
                        {
                            alExt.alGenFilters(1, &filter[filters]);
                            if (alGetError() != AL_NO_ERROR)
                                break;
                        }
                    }
                }
                else
                {
                    soundContext = alcCreateContext ( soundDevice, NULL );
                    alcMakeContextCurrent ( soundContext );
                }

                // Set default settings for the listener
                ALfloat orient[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
                alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
                alListenerfv(AL_ORIENTATION, orient);
                alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
            }

#ifdef WITHSDL
            if (Sound_Init() == 0)
                //*output << "Audio device error: " << Sound_GetError() << "\n";

            const Sound_DecoderInfo **temp = Sound_AvailableDecoders();
#endif
        }

        // destructor that clears all the buffers
        AudioDriver::~AudioDriver()
        {
            //for (unsigned int i = 0; i < audioSourcePointers.size(); ++i)
            //    audioSourcePointers[i]->drop();
            for (std::map<unsigned int, AudioSource*>::iterator it = audioSourcePointers.begin(); it != audioSourcePointers.end(); ++it)
            {
                (*it).second->drop();
                (*it).second->device = NULL;
            }
            audioSourcePointers.clear();
#ifdef WITHSDL
            Sound_Quit();
#endif
        }

        void AudioDriver::flush()
        {
            for (std::map<unsigned int, AudioSource*>::iterator it = audioSourcePointers.begin(); it != audioSourcePointers.end(); ++it)
                it->second->drop();

            audioSourcePointers.clear();
        }

        // Create a new source
        AudioSource* AudioDriver::createASource(SoundData *data)
        {
            AudioSource *source = new AudioSource(this, sourceCount);
            source->attachSound(data);
            audioSourcePointers[sourceCount++] = source;
            return source;
        }

        void AudioDriver::attachAudioSource(AudioSource *aSource)
        {
            aSource->device = this;
            aSource->setSourceId(sourceCount);
            audioSourcePointers[sourceCount++] = aSource;
        }

        void AudioDriver::playAll()
        {
            if (!active)
                return;
            std::map<unsigned int, AudioSource *>::iterator it = audioSourcePointers.begin();
            while (it != audioSourcePointers.end())
                (*it++).second->updateBuffer();
        }

        void AudioDriver::setListenerPosition(const float &x, const float &y, const float &z)
        {
            alListener3f(AL_POSITION, x, y, z);
            lpX = x;
            lpY = y;
            lpZ = z;
        }

        void AudioDriver::setListenerVelocity(const float &x, const float &y, const float &z)
        {
            alListener3f(AL_VELOCITY, x, y, z);
            lvX = x;
            lvY = y;
            lvZ = z;
        }

        void AudioDriver::setListenerOrient(const float &x, const float &y, const float &z)
        {
            alListener3f(AL_ORIENTATION, x, y, z);
            loX = x;
            loY = y;

            loZ = z;
        }

        void AudioDriver::setEffect(const unsigned int &auxSlotId, const unsigned int &effectSlotId, AudioEffect *aEffect)
        {
            if (auxSlotId > effectSlots || effectSlotId > effects)
                return;

            aEffect->device = this;
            aEffect->activate(effectSlot[auxSlotId], effect[effectSlotId]);
        }

        void AudioDriver::genEffectSlot(unsigned int *efSlot)
        {
            if (usedEffectSlots > effectSlots)
            {
                return;
            }
            *efSlot = usedEffectSlots++;
        }

        void AudioDriver::genEffect(unsigned int *eff)
        {
            if (usedEffects > effects)
            {
                return;
            }
            *eff = usedEffects++;
        }

        void AudioDriver::genFilter(unsigned int *filt)
        {
            if (usedEffects > effects)
            {
                return;
            }
            *filt = usedFilters++;
        }

        /*
        	Audio Sources
        */
        AudioSource::AudioSource(AudioDriver *AudioDriver = NULL, const unsigned int &newSourceId = 0, const unsigned int &buffSize)
        {
            device = AudioDriver;
            sourceId = newSourceId;
            sData = NULL;
            bufferSize = buffSize;
            buffer = new char[bufferSize * 16];

            alGenBuffers(2, alBuffer);
            alGenSources(1, &sourceId);

            alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
            alSource3f(sourceId, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
            alSource3f(sourceId, AL_DIRECTION, 0.0f, 0.0f, 0.0f);
            alSourcef(sourceId, AL_PITCH, 1.0f);
            alSourcef(sourceId, AL_GAIN, 1.0f);
            alSourcef(sourceId, AL_ROLLOFF_FACTOR, 1.0f);

            if (device != NULL)
                if (device->audioSourcePointers.find(sourceId) == device->audioSourcePointers.end())
                    device->audioSourcePointers[sourceId] = this;
        }

        AudioSource::~AudioSource()
        {
            if (sData != NULL)
                sData->drop();

            if (device != NULL)
                device->audioSourcePointers.erase(device->audioSourcePointers.find(sourceId));

            delete [] buffer;
        }

        void AudioSource::attachSound(SoundData *soundData)
        {
            if (soundData == NULL)
                return;
            sData = soundData;
            sData->attachedSources.push_back(this);
#ifdef WITHSDL
            if (sData->typeLoaded == sData->FT_OTHER)
                Sound_SetBufferSize(sData->osound, bufferSize * 16);
#endif
        }

        void AudioSource::setSourceId(const unsigned int &newId)
        {
            sourceId = newId;
        }

        void AudioSource::rewind()
        {
            soundPosition = 0;
            if (sData != NULL)
                sData->rewind();
        }

        bool AudioSource::updateBuffer(const bool &firstPlay)
        {
            if (sData == NULL)
                return false;

            if (firstPlay)
            {
                if (!sData->readSamples(this, alBuffer[0]))
                    return false;
                if (!sData->readSamples(this, alBuffer[1]))
                    return false;

                alSourceQueueBuffers(sourceId, 2, alBuffer);
                return true;
            }

            ALenum state;
            alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
            if (state == AL_STOPPED || state == AL_PAUSED)
                return false;

            int done = 0;
            alGetSourcei(sourceId, AL_BUFFERS_PROCESSED, &done);

            while (done--)
            {
                ALuint buffer;
                alSourceUnqueueBuffers(sourceId, 1, &buffer);
                if (!sData->readSamples(this, buffer))
                    return false;
                alSourceQueueBuffers(sourceId, 1, &buffer);
            }
            return true;
        }

        bool AudioSource::isPlaying() const
        {
            ALenum state;
            alGetSourcei(sourceId, AL_SOURCE_STATE, &state);
            return (state == AL_PLAYING);
        }

        bool AudioSource::play()
        {
            if (!device->active)
                return false;

            if (sData == NULL)
                return false;

            if (isPlaying())
                return true;

            // reset the sound position
            soundPosition = 0;

            if (!updateBuffer(true))
                return false;

            alSourcePlay(sourceId);
            return true;
        }

        void AudioSource::stop()
        {
            alSourceStop(sourceId);

            int done;
            alGetSourcei(sourceId, AL_BUFFERS_PROCESSED, &done);

            while (done--)
            {
                ALuint buffer;
                alSourceUnqueueBuffers(sourceId, 1, &buffer);
            }

            rewind();
        }

        void AudioSource::pause()
        {
            alSourcePause(sourceId);
        }

        void AudioSource::setLoop(const bool &looping)
        {
            loop = looping;
        }

        void AudioSource::setVolume(const float &newVolume)
        {
            if (newVolume > 1.0f)
                volume = 1.0f;
            else if (newVolume < 0.0f)
                volume = 0.0f;
            else
                volume = newVolume;

            alSourcef(sourceId, AL_GAIN, volume);
        }

        void AudioSource::setAttenuation(const float &attenuation)
        {
            if (attenuation < 0.0f)
                attn = 0.0f;
            else
                attn = attenuation;

            alSourcef(sourceId, AL_ROLLOFF_FACTOR, attn);
        }

        void AudioSource::setPosition(const float &x, const float &y, const float &z)
        {
            alSource3f(sourceId, AL_POSITION, x, y, z);
            X = X;
            Y = y;
            Z = z;
        }

        void AudioSource::setRelative(const bool &relative)
        {
            alSourcei(sourceId, AL_SOURCE_RELATIVE, relative?AL_TRUE:AL_FALSE);
        }

        void AudioSource::passThroughEffectSlot(const unsigned int &slotNumber)
        {
            alSource3i(sourceId, AL_AUXILIARY_SEND_FILTER, device->effectSlot[slotNumber], 0, 0);

            if (alGetError() != AL_NO_ERROR)
            printf("Could not set the pass through");
            //    *device->output << "Could not set the pass through" << "\n";
        }

        /*
        	Sound Data
        */
        SoundData* SoundData::LoadAudio(AudioDriver *device, const std::string &filename, const bool &loadToMemory = false)
        {
            FILE *f;
            if (!(f = fopen(filename.c_str(), "rb")))
            {
                //*device->output << "Could not load: " << filename.c_str() << "\n";
                return NULL;
            }
            else
            {
                fclose(f);
                return new SoundData(filename, loadToMemory);
            }
        }

        SoundData::SoundData(const std::string &filename, const bool &loadToMemory = false)
        {
            std::string extension = filename.substr ( filename.rfind(".") + 1);
            #ifdef OGG
            if ( extension == "ogg" )
            {
                ogg = new OggFile();
                ogg->open(filename, loadToMemory);
                typeLoaded = FT_OGG;
            }
            #endif
#ifdef WITHSDL
             if ( extension == "mp3" )
            {
                if (enableMp3Playback)
                {
                    osound = Sound_NewSampleFromFile(filename.c_str(), NULL, 512);
                    typeLoaded = FT_OTHER;
                }
                else
                    typeLoaded = FT_NULL;
            }
            else if ( extension == "wav" )
            {
                osound = Sound_NewSampleFromFile(filename.c_str(), NULL, 512);
                typeLoaded = FT_OTHER;
            }
            else if ( extension == "mod" )
            {
                osound = Sound_NewSampleFromFile(filename.c_str(), NULL, 512);
                typeLoaded = FT_OTHER;
            }
            else if ( extension == "it")
            {
                osound = Sound_NewSampleFromFile(filename.c_str(), NULL, 512);
                typeLoaded = FT_OTHER;
            }
            else if ( extension == "s3m" )
            {
                osound = Sound_NewSampleFromFile(filename.c_str(), NULL, 512);
                typeLoaded = FT_OTHER;
            }
            else if ( extension == "midi" )
            {
                osound = Sound_NewSampleFromFile(filename.c_str(), NULL, 512);
                typeLoaded = FT_OTHER;
            }
#endif
            else
                typeLoaded = FT_NULL;

#ifdef WITHSDL
            if (osound == NULL && typeLoaded == FT_OTHER)
            {
                typeLoaded = FT_NULL;
                //*output << "Sound Error: " << extension.c_str() << " " << Sound_GetError() << "\n";
                //*output << "Failed to open " << filename.c_str() << "\n";
            }
            //else
            //    *output << "Sound: " << filename.c_str() << " loaded" << "\n";
#endif
        }

        SoundData::~SoundData()
        {
            if (typeLoaded == FT_OGG)
            {
                ogg->close();
                delete ogg;
                ogg = NULL;
            }
#ifdef WITHSDL
            else if (typeLoaded == FT_OTHER)
                Sound_FreeSample(osound);
#endif

            for (std::vector<AudioSource*>::iterator it = attachedSources.begin(); it != attachedSources.end(); ++it)
                (*it)->sData = NULL;

            attachedSources.clear();
        }

        void SoundData::attachToAudioSource(AudioSource *audioSource)
        {
            audioSource->attachSound(this);
#ifdef WITHSDL
            if (typeLoaded == FT_OTHER)
                Sound_SetBufferSize(osound, audioSource->bufferSize * 16);
#endif

            attachedSources.push_back(audioSource);
        }

        void SoundData::rewind()
        {
            if (typeLoaded == FT_OGG)
                ogg->rewind();
#ifdef WITHSDL
            else if (typeLoaded != FT_NULL)
                Sound_Rewind(osound);
#endif
        }

        bool SoundData::readSamples(AudioSource *source, ALuint bufferId)
        {
            int section, result;
            unsigned int size = 0;

            if (typeLoaded == FT_OGG)
            {
                ogg->setPosition(source->soundPosition);
                while (size < (source->bufferSize * 16))
                {
                    if (ogg->getPosition() >= ogg->samples() - 20)
                    {
                        if (source->loop)
                            ogg->rewind();
                        else if (size == 0)
                        {
                            ogg->rewind();
                            source->stop();
                        }
                        else
                            break;
                    }
#ifdef __powerpc__
                    result = ogg->read(source->buffer + size, (source->bufferSize * 16)-size, 1, 2, 1, &section);
#else
                    result = ogg->read(source->buffer + size, (source->bufferSize * 16)-size, 0, 2, 1, &section);
#endif
                    if (result >= 0)
                        size+=result;
                }
                source->soundPosition = ogg->getPosition();
            }
#ifdef WITHSDL
            else if (typeLoaded != FT_NULL)
            {
                size = Sound_Decode(osound);
                if (size != osound->buffer_size)
                {
                    if (osound->flags & SOUND_SAMPLEFLAG_EOF)
                    {
                        if (size <= 20)
                        {
                            if (source->loop)
                                Sound_Rewind(osound);
                            else if (size == 0)
                                source->stop();
                        }
                    }
                }
            }
#endif

            if (size == 0)
                return false;

            if (typeLoaded == FT_OGG)
                ogg->bufferthis(&bufferId, source->buffer, size);
#ifdef WITHSDL
            else if (typeLoaded == FT_OTHER)
                alBufferData(bufferId, (osound->actual.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, osound->buffer, size, osound->actual.rate);
#endif

            if (alGetError() != AL_NO_ERROR)
            {
                //*output << "Audio Error: Problem buffering audio" << "\n";
                return false;
            }

            return true;
        }

        AudioEffect::AudioEffect(const audioEffects &eType)
        {
            effectType = eType;

            // Default settings for effects

            // Reverb
            reverbDensity = 1.0f;
            reverbDiffusion = 1.0f;
            reverbGain = 0.32f;
            reverbGainHf = 0.89f;
            reverbDecayTime = 1.49f;
            reverbDecayHfRatio = 0.83f;
            reverbReflectionsGain = 0.5f;
            reverbReflectionsDelay = 0.007f;
            reverbLateReverbGain = 1.26f;
            reverbLateReverbDelay = 0.011f;
            reverbAirAbsorptionGainHf = 0.994f;
            reverbRoomRolloffFactor = 0.0f;
            reverbDecayHfLimit = AL_TRUE;

            // Chorus
            chorusWaveform = AL_CHORUS_WAVEFORM_TRIANGLE;
            chorusPhase = 90;
            chorusRate = 1.1f;
            chorusDepth = 0.1f;
            chorusFeedback = 0.25f;
            chorusDelay = 0.016f;

            // Distortion
            distortionEdge = 0.2f;
            distortionGain = 0.05f;
            distortionLowpassCutoff = 8000.0f;
            distortionEQCenter = 3600.0f;
            distortionEQBandwidth = 3600.0f;

            // Echo
            echoDelay = 0.1f;
            echoLRDelay = 0.1f;
            echoDamping = 0.5f;
            echoFeedback = 0.5f;
            echoSpread = -1.0f;

            // Flanger
            flangerWaveform = AL_FLANGER_WAVEFORM_TRIANGLE;
            flangerPhase = 0;
            flangerRate = 0.27f;
            flangerDepth = 1.0f;
            flangerFeedback = -0.5f;
            flangerDelay = 0.002f;

            // Frequency Shifter
            shifterFrequency = 0.0f;
            shifterLeftDirection = 0;
            shifterRightDirection = 0;

            // Vocal Morpher
            morpherPhonemeA = 0;
            morpherPhonemeB = 10;
            morpherPhonemeACoarseTuning = 0;
            morpherPhonemeBCoarseTuning = 0;
            morpherWaveform = 0;
            morpherRate = 1.41f;

            // Pitch shifter
            shifterCoarseTune = 12;
            shifterFineTune = 0;

            // Ring Modulator
            ringModulatorFrequency = 440.0f;
            ringModulatorHighpassCutoff = 800.0f;
            ringModulatorWaveform = 0;

            // AutoWAH
            autowahAttackTime = 0.06f;
            autowahReleaseTime = 0.06f;
            autowahResonance = 1000.0f;
            autowahPeakGain = 11.22f;

            // Compressor
            compressorOnOff = 1;

            // Equalizer
            eqLowGain = 1.0f;
            eqLowCutoff = 200.0f;
            eqMid1Gain = 1.0f;
            eqMid1Center = 500.0f;
            eqMid1Width = 1.0f;
            eqMid2Gain = 1.0f;
            eqMid2Center = 3000.0f;
            eqMid2Width = 1.0f;
            eqHighGain = 1.0f;
            eqHighCutoff = 6000.0f;
        }

        // Activates the audio effect type
        void AudioEffect::activate(const unsigned int &effectSlot, const unsigned int &effects)
        {
            auxSlot = effectSlot;
            effect = device->effect[effects];
            switch (effectType)
            {
            case EFFECT_REVERB:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
                device->alExt.alEffectf(effect, AL_REVERB_DENSITY, reverbDensity);
                device->alExt.alEffectf(effect, AL_REVERB_DIFFUSION, reverbDiffusion);
                device->alExt.alEffectf(effect, AL_REVERB_GAIN, reverbGain);
                device->alExt.alEffectf(effect, AL_REVERB_GAINHF, reverbGainHf);
                device->alExt.alEffectf(effect, AL_REVERB_DECAY_TIME, reverbDecayTime);
                device->alExt.alEffectf(effect, AL_REVERB_DECAY_HFRATIO, reverbDecayHfRatio);
                device->alExt.alEffectf(effect, AL_REVERB_REFLECTIONS_GAIN, reverbReflectionsGain);
                device->alExt.alEffectf(effect, AL_REVERB_REFLECTIONS_DELAY, reverbReflectionsDelay);
                device->alExt.alEffectf(effect, AL_REVERB_LATE_REVERB_GAIN, reverbLateReverbGain);
                device->alExt.alEffectf(effect, AL_REVERB_LATE_REVERB_DELAY, reverbLateReverbDelay);
                device->alExt.alEffectf(effect, AL_REVERB_AIR_ABSORPTION_GAINHF, reverbAirAbsorptionGainHf);
                device->alExt.alEffectf(effect, AL_REVERB_ROOM_ROLLOFF_FACTOR, reverbRoomRolloffFactor);
                device->alExt.alEffecti(effect, AL_REVERB_DECAY_HFLIMIT, reverbDecayHfLimit);
                break;
            case EFFECT_CHORUS:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
                device->alExt.alEffecti(effect, AL_CHORUS_WAVEFORM, chorusWaveform);
                device->alExt.alEffecti(effect, AL_CHORUS_PHASE, chorusPhase);
                device->alExt.alEffectf(effect, AL_CHORUS_RATE, chorusRate);
                device->alExt.alEffectf(effect, AL_CHORUS_DEPTH, chorusDepth);
                device->alExt.alEffectf(effect, AL_CHORUS_FEEDBACK, chorusFeedback);
                device->alExt.alEffectf(effect, AL_CHORUS_DELAY, chorusDelay);
                break;
            case EFFECT_DISTORTION:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
                device->alExt.alEffectf(effect, AL_DISTORTION_EDGE, distortionEdge);
                device->alExt.alEffectf(effect, AL_DISTORTION_GAIN, distortionGain);
                device->alExt.alEffectf(effect, AL_DISTORTION_LOWPASS_CUTOFF, distortionLowpassCutoff);
                device->alExt.alEffectf(effect, AL_DISTORTION_EQCENTER, distortionEQCenter);
                device->alExt.alEffectf(effect, AL_DISTORTION_EQBANDWIDTH, distortionEQBandwidth);
                break;
            case EFFECT_ECHO:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_ECHO);
                device->alExt.alEffectf(effect, AL_ECHO_DELAY, echoDelay);
                device->alExt.alEffectf(effect, AL_ECHO_LRDELAY, echoLRDelay);
                device->alExt.alEffectf(effect, AL_ECHO_DAMPING, echoDamping);
                device->alExt.alEffectf(effect, AL_ECHO_FEEDBACK, echoFeedback);
                device->alExt.alEffectf(effect, AL_ECHO_SPREAD, echoSpread);
                break;
            case EFFECT_FLANGER:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_FLANGER);
                device->alExt.alEffecti(effect, AL_FLANGER_WAVEFORM, flangerWaveform);
                device->alExt.alEffecti(effect, AL_FLANGER_PHASE, flangerPhase);
                device->alExt.alEffectf(effect, AL_FLANGER_RATE, flangerRate);
                device->alExt.alEffectf(effect, AL_FLANGER_DEPTH, flangerDepth);
                device->alExt.alEffectf(effect, AL_FLANGER_FEEDBACK, flangerFeedback);
                device->alExt.alEffectf(effect, AL_FLANGER_DELAY, flangerDelay);
                break;
            case EFFECT_FREQUENCY_SHIFTER:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_FREQUENCY_SHIFTER);
                device->alExt.alEffectf(effect, AL_FREQUENCY_SHIFTER_FREQUENCY, shifterFrequency);
                device->alExt.alEffecti(effect, AL_FREQUENCY_SHIFTER_LEFT_DIRECTION, shifterLeftDirection);
                device->alExt.alEffecti(effect, AL_FREQUENCY_SHIFTER_RIGHT_DIRECTION, shifterRightDirection);
                break;
            case EFFECT_VOCAL_MORPHER:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_VOCAL_MORPHER);
                device->alExt.alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEA, morpherPhonemeA);
                device->alExt.alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEB, morpherPhonemeB);
                device->alExt.alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEA_COARSE_TUNING, morpherPhonemeACoarseTuning);
                device->alExt.alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEB_COARSE_TUNING, morpherPhonemeBCoarseTuning);
                device->alExt.alEffecti(effect, AL_VOCAL_MORPHER_WAVEFORM, morpherWaveform);
                device->alExt.alEffectf(effect, AL_VOCAL_MORPHER_RATE, morpherRate);
                break;
            case EFFECT_PITCH_SHIFTER:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_PITCH_SHIFTER);
                device->alExt.alEffecti(effect, AL_PITCH_SHIFTER_COARSE_TUNE, shifterCoarseTune);
                device->alExt.alEffecti(effect, AL_PITCH_SHIFTER_FINE_TUNE, shifterFineTune);
                break;
            case EFFECT_RING_MODULATOR:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_RING_MODULATOR);
                device->alExt.alEffectf(effect, AL_RING_MODULATOR_FREQUENCY, ringModulatorFrequency);
                device->alExt.alEffectf(effect, AL_RING_MODULATOR_HIGHPASS_CUTOFF, ringModulatorHighpassCutoff);
                device->alExt.alEffecti(effect, AL_RING_MODULATOR_WAVEFORM, ringModulatorWaveform);
                break;
            case EFFECT_AUTOWAH:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_AUTOWAH);
                device->alExt.alEffectf(effect, AL_AUTOWAH_ATTACK_TIME, autowahAttackTime);
                device->alExt.alEffectf(effect, AL_AUTOWAH_RELEASE_TIME, autowahReleaseTime);
                device->alExt.alEffectf(effect, AL_AUTOWAH_RESONANCE, autowahResonance);
                device->alExt.alEffectf(effect, AL_AUTOWAH_PEAK_GAIN, autowahPeakGain);
                break;
            case EFFECT_EQUALIZER:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_EQUALIZER);
                device->alExt.alEffectf(effect, AL_EQUALIZER_LOW_GAIN, eqLowGain);
                device->alExt.alEffectf(effect, AL_EQUALIZER_LOW_CUTOFF, eqLowCutoff);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID1_GAIN, eqMid1Gain);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID1_CENTER, eqMid1Center);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID1_WIDTH, eqMid1Width);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID2_GAIN, eqMid2Gain);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID2_CENTER, eqMid2Center);
                device->alExt.alEffectf(effect, AL_EQUALIZER_MID2_WIDTH, eqMid2Width);
                device->alExt.alEffectf(effect, AL_EQUALIZER_HIGH_GAIN, eqHighGain);
                device->alExt.alEffectf(effect, AL_EQUALIZER_HIGH_CUTOFF, eqHighCutoff);
                break;
            case EFFECT_COMPRESSOR:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_COMPRESSOR);
                device->alExt.alEffecti(effect, AL_COMPRESSOR_ONOFF, compressorOnOff);
                break;
            case EFFECT_NULL:
            default:
                device->alExt.alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_NULL);
                break;
            }

            device->alExt.alAuxiliaryEffectSloti(auxSlot, AL_EFFECTSLOT_EFFECT, effect);
   printf("teste" );
            if (alGetError() != AL_NO_ERROR){
        //        *device->output << "Problem loading the effect" << "\n";
         printf("Problem loading the effect" );
            }
        }

        // Instantiates a new audio device
        AudioDriver *createAudioDevice()
        {
            if (AudioDriver::instance == NULL)
            {
                return AudioDriver::instance = new AudioDriver();
            }
            else
                return AudioDriver::instance;
        }








        /* =================================================================================================================================================
        ====================================================================================================================================================
        ====================================================================================================================================================
        ====================================================================================================================================================
        ====================================================================================================================================================

        Effect Types/Presets are below here.

        ====================================================================================================================================================
        ====================================================================================================================================================
        ====================================================================================================================================================
        ====================================================================================================================================================
        ====================================================================================================================================================*/

        // Reverb
        void AudioEffect::setReverbType(const reverbType &reverb)
        {
            switch (reverb)
            {
            case REVERB_PLATE:
                break;
            case REVERB_NULL:
            default:
                break;
            }
        }
    }
}


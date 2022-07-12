#ifndef AUDIO_H
#define AUDIO_H
#include <string>
#include <map>
#include <vector>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

#ifdef WITHSDL
#include <SDL/SDL_sound.h>
#endif

#include "CVorbisFile.h"

#include "IReferenceCounted.h"

#define OGG

namespace agEngine
{
    namespace Audio
    {
        typedef enum
        {
            EFFECT_NULL,
            EFFECT_REVERB,
            EFFECT_CHORUS,
            EFFECT_DISTORTION,
            EFFECT_ECHO,
            EFFECT_FLANGER,
            EFFECT_FREQUENCY_SHIFTER,
            EFFECT_VOCAL_MORPHER,
            EFFECT_PITCH_SHIFTER,
            EFFECT_RING_MODULATOR,
            EFFECT_AUTOWAH,
            EFFECT_COMPRESSOR,
            EFFECT_EQUALIZER,
            EFFECT_EAXREVERB
        } audioEffects;

        typedef enum
        {
            REVERB_NULL,
            REVERB_PLATE,
            REVERB_ROOM,
            REVERB_HALL,
            REVERB_AUDITORIUM,
            REVERB_ARENA,
            REVERB_HANGAR,
            REVERB_MOUNTAIN,
        } reverbType;

        // OpenAL extensions
        typedef struct
        {
            // Effect object functions
            LPALGENEFFECTS alGenEffects;
            LPALDELETEEFFECTS alDeleteEffects;
            LPALISEFFECT alIsEffect;
            LPALEFFECTI alEffecti;
            LPALEFFECTIV alEffectiv;
            LPALEFFECTF alEffectf;
            LPALEFFECTFV alEffectfv;
            LPALGETEFFECTI alGetEffecti;
            LPALGETEFFECTIV alGetEffectiv;
            LPALGETEFFECTF alGetEffectf;
            LPALGETEFFECTFV alGetEffectfv;

            // Filter object functions
            LPALGENFILTERS alGenFilters;
            LPALDELETEFILTERS alDeleteFilters;
            LPALISFILTER alIsFilter;
            LPALFILTERI alFilteri;
            LPALFILTERIV alFilteriv;
            LPALFILTERF alFilterf;
            LPALFILTERFV alFilterfv;
            LPALGETFILTERI alGetFilteri;
            LPALGETFILTERIV alGetFilteriv;
            LPALGETFILTERF alGetFilterf;
            LPALGETFILTERFV alGetFilterfv;

            // Auxiliary slot object functions
            LPALGENAUXILIARYEFFECTSLOTS alGenAuxiliaryEffectSlots;
            LPALDELETEAUXILIARYEFFECTSLOTS alDeleteAuxiliaryEffectSlots;
            LPALISAUXILIARYEFFECTSLOT alIsAuxiliaryEffectSlot;
            LPALAUXILIARYEFFECTSLOTI alAuxiliaryEffectSloti;
            LPALAUXILIARYEFFECTSLOTIV alAuxiliaryEffectSlotiv;
            LPALAUXILIARYEFFECTSLOTF alAuxiliaryEffectSlotf;
            LPALAUXILIARYEFFECTSLOTFV alAuxiliaryEffectSlotfv;
            LPALGETAUXILIARYEFFECTSLOTI alGetAuxiliaryEffectSloti;
            LPALGETAUXILIARYEFFECTSLOTIV alGetAuxiliaryEffectSlotiv;
            LPALGETAUXILIARYEFFECTSLOTF alGetAuxiliaryEffectSlotf;
            LPALGETAUXILIARYEFFECTSLOTFV alGetAuxiliaryEffectSlotfv;

        } EFX_EXTENSION_STRUCT;

        class AudioSource;
        class SoundData;
        class AudioEffect;

        class AudioDriver : public virtual irr::IReferenceCounted
        {
        public:
            AudioDriver();

            AudioSource *createASource(SoundData *soundData);
            void attachAudioSource(AudioSource *aSource);

            void playAll();
            void flush();

            void setListenerPosition(const float &x, const float &y, const float &z);
            void setListenerVelocity(const float &x, const float &y, const float &z);
            void setListenerOrient(const float &x, const float &y, const float &z);

            bool isActive() const
            {
                return active;
            }
            AudioDriver *getInstance() const
            {
                return instance;
            }
            bool hasEffectExtension();

            unsigned int getAuxSlotsAvailable() const;
            unsigned int getEffectsAvailable() const;
            unsigned int getFiltersAvailable() const;

            void genEffectSlot(unsigned int *slot);
            void genEffect(unsigned int *effect);
            void genFilter(unsigned int *filter);

            void setEffect(const unsigned int &auxSlotId, const unsigned int &effectSlotId, AudioEffect *aEffect);

            static AudioDriver *instance;

            float lpX, lpY, lpZ;
            float lvX, lvY, lvZ;
            float loX, loY, loZ;
        protected:
            ~AudioDriver();
        private:
            ALCcontext *soundContext;
            ALCdevice *soundDevice;

            bool active;
            bool effectsEnabled;

            // Pointers to the data
            unsigned int sourceCount;
            std::map<unsigned int, AudioSource *> audioSourcePointers;

            // OpenAL extensions
            EFX_EXTENSION_STRUCT alExt;
            ALuint effectSlot[16];
            ALuint effect[16];
            ALuint filter[16];

            unsigned int effectSlots;
            unsigned int effects;
            unsigned int filters;

            unsigned int usedEffectSlots;
            unsigned int usedEffects;
            unsigned int usedFilters;

            friend class AudioSource;
            friend class SoundData;
            friend class AudioEffect;
        };

        class AudioSource : public virtual irr::IReferenceCounted
        {
        public:
            AudioSource(AudioDriver *device, const unsigned int &sourceId, const unsigned int &bufferSize=32768);

            void attachSound(SoundData *soundData);
            bool play();
            void stop();
            void pause();
            void rewind();
            bool isPlaying() const;

            void setLoop(const bool &loop);
            void setVolume(const float &volume);
            void setAttenuation(const float &attn);
            void setRelative(const bool &relative);

            void setPosition(const float &x, const float &y, const float &z);

            void passThroughEffectSlot(const unsigned int &slotNumber);

            float X,Y,Z;

        protected:
            ~AudioSource();

        private:
            bool updateBuffer(const bool &firstPlay = false);
            void setSourceId(const unsigned int &sourceId);

            unsigned int sourceId;

            SoundData *sData;
            AudioDriver *device;

            ALuint alBuffer[2];

            unsigned int bufferSize;
            char *buffer;
            unsigned int soundPosition;

            bool loop;
            float volume;
            float attn;

            friend class AudioDriver;
            friend class SoundData;
            friend class AudioEffect;
        };

        class SoundData : public virtual irr::IReferenceCounted
        {
        public:
            static SoundData *LoadAudio(AudioDriver *device, const std::string &fileName, const bool &loadToMemory);

            void attachToAudioSource(AudioSource *audioSource);

        protected:
            ~SoundData();

        private:
            SoundData(const std::string &fileName, const bool &loadToMemory);

            void rewind();
            bool readSamples(AudioSource *source, ALuint bufferId);

            enum fileType
            {
                FT_NULL,
                FT_OGG,
                FT_OTHER,
            };

            fileType typeLoaded;

            unsigned int soundId;

            AudioDriver *device;
#ifdef OGG
            OggFile *ogg;
#endif
#ifdef WITHSDL
            Sound_Sample *osound;
#endif

            std::vector<AudioSource*> attachedSources;

            friend class AudioSource;
        };

        class AudioEffect
        {
        public:
            AudioEffect(const audioEffects &effectType);
            void setReverbType(const reverbType &reverb);
        protected:
            ~AudioEffect();
        private:
            void activate(const unsigned int &auxSlot, const unsigned int &effectSlot);
            audioEffects effectType;

            AudioDriver *device;
            ALuint effect;
            ALuint auxSlot;

            friend class AudioDriver;

        private:
            // These are all the variables used to set the different effects

            // Reverb
            float reverbDensity;
            float reverbDiffusion;
            float reverbGain;
            float reverbGainHf;
            float reverbDecayTime;
            float reverbDecayHfRatio;
            float reverbReflectionsGain;
            float reverbReflectionsDelay;
            float reverbLateReverbGain;
            float reverbLateReverbDelay;
            float reverbAirAbsorptionGainHf;
            float reverbRoomRolloffFactor;
            int reverbDecayHfLimit;

            // Chorus
            int chorusWaveform;
            int chorusPhase;
            float chorusRate;
            float chorusDepth;
            float chorusFeedback;
            float chorusDelay;

            // Distortion
            float distortionEdge;
            float distortionGain;
            float distortionLowpassCutoff;
            float distortionEQCenter;
            float distortionEQBandwidth;

            // Echo
            float echoDelay;
            float echoLRDelay;
            float echoDamping;
            float echoFeedback;
            float echoSpread;

            // Flanger
            int flangerWaveform;
            int flangerPhase;
            float flangerRate;
            float flangerDepth;
            float flangerFeedback;
            float flangerDelay;

            // Frequency Shifter
            float shifterFrequency;
            unsigned int shifterLeftDirection;
            unsigned int shifterRightDirection;

            // Vocal Morpher
            unsigned int morpherPhonemeA;
            unsigned int morpherPhonemeB;
            int morpherPhonemeACoarseTuning;
            int morpherPhonemeBCoarseTuning;
            unsigned int morpherWaveform;
            float morpherRate;

            // Pitch Shifter
            int shifterCoarseTune;
            int shifterFineTune;

            // Ring Modulator
            float ringModulatorFrequency;
            float ringModulatorHighpassCutoff;
            int ringModulatorWaveform;

            // Autowah
            float autowahAttackTime;
            float autowahReleaseTime;
            float autowahResonance;
            float autowahPeakGain;

            // Equalizer
            float eqLowGain;
            float eqLowCutoff;
            float eqMid1Gain;
            float eqMid1Center;
            float eqMid1Width;
            float eqMid2Gain;
            float eqMid2Center;
            float eqMid2Width;
            float eqHighGain;
            float eqHighCutoff;

            // Compressor
            int compressorOnOff;
        };

        AudioDriver *createAudioDevice();
    }
}

#endif

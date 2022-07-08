#pragma once
#include "../../config.h"
#ifdef AGAUDIO3
#include <irrlicht.h>
#ifdef WIN32
#include <al.h>
#include <alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
#include "CAudioSource.h"

using namespace irr;

namespace agEngine
{
    namespace audio
    {
        class CAudioSource;
        class CAudioStream;

        class CAudioDevice : public virtual IReferenceCounted
        {
        public:
            CAudioDevice();
            virtual ~CAudioDevice();

            virtual CAudioSource* createAudioSource(CAudioStream* stream = 0);
            virtual void addAudioSource(CAudioSource* newSource);

            virtual CAudioStream* createAudioStream(const c8* filename, bool loadToMemory = false);

            virtual void playAll();
            virtual void clear();

            void playBuffer(char* buffer, long nBytes);

            virtual void setListenerPosition(const core::vector3d<float>& newPosition);
            virtual void setListenerVelocity(const core::vector3d<float>& newVelocity);
            virtual void setListenerOrientation(const core::vector3d<float>& orient1, const core::vector3d<float>& orient2);

            virtual u32 getNextAvailableSourceId();

        private:
            core::array<CAudioSource*> sources;

            bool active;

            ALCcontext *sContext;
            ALCdevice *sDevice;

            u32 sourceCount;
        };
    }
}
#endif


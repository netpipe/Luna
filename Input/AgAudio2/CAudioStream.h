#include "../../config.h"
#ifdef AgAudio2
#ifndef _CAUDIOSTREAM_H_
#define _CAUDIOSTREAM_H_

#include <irrlicht.h>
#ifdef WIN32
#include <al.h>
#else
#include <AL/al.h>
#endif

#include "CAudioSource.h"
#include "CAudioData.h"

using namespace irr;

namespace agEngine
{
    namespace audio
    {
        class CAudioSource;
        class CAudioData;

        class CAudioStream : public virtual IReferenceCounted
        {
        public:
            CAudioStream(CAudioData* data=0);
            virtual ~CAudioStream();

            virtual void attachAudioData(CAudioData* data);
            virtual void detatchAudioData();

            virtual void rewind();
            virtual bool readSamples(CAudioSource* source, ALuint bufferId);

            virtual bool hasFinished() const;

        private:
            CAudioData* attachedData;
        };
    }
}

#endif
#endif

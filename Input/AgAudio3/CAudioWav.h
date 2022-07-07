#pragma once
#include "../../config.h"
#ifdef AGAUDIO3
#include <irrlicht.h>

#include <AL/al.h>

#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include "CAudioData.h"

using namespace irr;

namespace agEngine
{
    namespace audio
    {
        struct SWavFile
        {
            char ChunkID[4];
            u32 ChunkSize;
            char Format[4];
            char Subchunk1ID[4];
            u32 Subchunk1Size;
            u16 AudioFormat;
            u16 NumChannels;
            u32 SampleRate;
            u32 ByteRate;
            u16 BlockAlign;
            u16 BitsPerSample;
            u32 Subchunk2Size;

            c8* dataPtr;
            u32 dataSize;
            u32 dataRead;
        };

        class CAudioWav : public CAudioData
        {
        public:
            CAudioWav(const core::stringc& filename, bool loadToMemory = false);
            ~CAudioWav();

            s32 open(const core::stringc& filename, bool loadToMemory = false);
            void close();
            u32 getSampleCount();
            u32 getPosition();
            void setPosition(u32 newPosition);
            f64 getLength();
            f64 getCurrentTime();
            void rewind();
            s32 read(c8* buffer, s32 size, s32 bigEndian, s32 word, s32 signedByte, s32* bitstream);
            void bufferthis(ALuint* buffer, c8* data, u32 size);
            bool readSamples(CAudioSource* source, ALuint bufferId);
            bool readMemorySamples(CAudioSource* source, ALuint bufferId, char* lpBuffer, long nBytes);
            bool hasFinished() const;
        private:
            FILE* file;
            SWavFile wavData;

            ALenum format;

            bool loadedInMemory;
            bool finished;
            u32 bufferSize;
        };
    }
}
#endif

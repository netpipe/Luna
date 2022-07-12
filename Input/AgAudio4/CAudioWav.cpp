#include "../../config.h"
#ifdef AGAUDIO3
#include "CAudioWav.h"
#define stricmp strcasecmp
#define strnicmp strncasecmp

namespace agEngine
{
    namespace audio
    {
        CAudioWav::CAudioWav(const core::stringc& filename, bool loadToMemory)
        : finished(false)
        {
            open(filename, loadToMemory);
        }

        CAudioWav::~CAudioWav()
        {
            close();
        }

        s32 CAudioWav::open(const core::stringc& filename, bool loadToMemory)
        {
            loadedInMemory = loadToMemory;

            if (!(file = fopen(filename.c_str(), "rb")))
            {
                loadedInMemory = true;
                return -1;
            }

            fread(wavData.ChunkID, 1, 4, file);
            fread(&wavData.ChunkSize, 4, 1, file);
            fread(wavData.Format, 1, 4, file);
            fread(wavData.Subchunk1ID, 1, 4, file);
            fread(&wavData.Subchunk1Size, 4, 1, file);
            fread(&wavData.AudioFormat, 2, 1, file);
            fread(&wavData.NumChannels, 2, 1, file);
            fread(&wavData.SampleRate, 4, 1, file);
            fread(&wavData.ByteRate, 4, 1, file);
            fread(&wavData.BlockAlign, 2, 1, file);
            fread(&wavData.BitsPerSample, 2, 1, file);

            for (int i = 0; i < 16; i += 4)
            {
                char tmp[5];
                fread(tmp, 1, 4, file);
                tmp[4] = 0;
                if(!stricmp(tmp, "data"))
                    break;
            }

            fread(&wavData.Subchunk2Size, 4, 1, file);

            int offset = ftell(file);
            fseek(file, 0, SEEK_END);
            u32 fileSize = ftell(file);

            fseek(file, offset, SEEK_SET);

            if (wavData.BitsPerSample == 16)
            {
                wavData.dataPtr = new c8[fileSize - offset];
                fread(wavData.dataPtr, 1, fileSize - offset, file);

                wavData.dataRead = 0;
                wavData.dataSize = fileSize - offset;
            }
            else if(wavData.BitsPerSample == 8)
            {
                c8* tmp_buf = new c8[fileSize - offset];
                fread(tmp_buf, 1, fileSize - offset, file);

                wavData.dataPtr = new c8[(fileSize - offset) * 2];

                for (long i = 0; i < (fileSize - offset); i++)
                {
                    int16_t sample16 = (int16_t)(tmp_buf[i] - 0x80) << 8;

                    memcpy(wavData.dataPtr + i * 2, &sample16, 2);

                    int pp = 0;
                }
                wavData.dataRead = 0;
                wavData.dataSize = (fileSize - offset) * 2;
            }

            if (wavData.NumChannels == 1)
            {
                format = AL_FORMAT_MONO16;
            }
            else
            {
                format = AL_FORMAT_STEREO16;
            }

            fclose(file);
            return 0;
        }

        void CAudioWav::bufferthis(ALuint *buffer, c8* data, u32 size)
        {
            alBufferData(*buffer, format, data, size, wavData.SampleRate);
        }

        u32 CAudioWav::getSampleCount()
        {
            u32 sample_count = wavData.Subchunk2Size / wavData.NumChannels / (wavData.BitsPerSample / 8);
            return sample_count;
        }

        u32 CAudioWav::getPosition()
        {
            u32 pos = wavData.dataRead;
            return pos;
        }

        void CAudioWav::setPosition(u32 pos)
        {
            wavData.dataRead = pos;
        }

        f64 CAudioWav::getLength()
        {
            f64 time = (f64)wavData.Subchunk2Size / wavData.NumChannels / (wavData.BitsPerSample / 8) / wavData.SampleRate;
            return time;
        }

        f64 CAudioWav::getCurrentTime()
        {
            f64 time = (f64)wavData.dataRead / wavData.NumChannels / (wavData.BitsPerSample / 8) / wavData.SampleRate;
            return time;
        }

        void CAudioWav::rewind()
        {
            wavData.dataRead = 0;
        }

        s32 CAudioWav::read(c8* buffer, s32 size, s32 bigEndian, s32 word, s32 signedByte, s32* bitstream)
        {
            memset(buffer, 0, size);

            if (wavData.dataRead + size >= wavData.dataSize)
                size = wavData.dataSize - wavData.dataRead;

            memcpy(buffer, wavData.dataPtr + wavData.dataRead, size);

            wavData.dataRead += size;

            return size;
        }

        void CAudioWav::close()
        {
            if (!loadedInMemory)
                fclose(file);
        }

        bool CAudioWav::readSamples(CAudioSource* source, ALuint bufferId)
        {
            s32 section, result;
            u32 size = 0;

            finished = false;

            u32 sBufferSize = source->getBufferSize();
            c8* sBuffer = source->getBuffer();

            setPosition(source->getStreamPosition());

            result = read(sBuffer, (sBufferSize * 16), 0, 2, 1, &section);

            source->setStreamPosition(getPosition());

            if (result == 0)
                finished = true;

            bufferthis(&bufferId, sBuffer, result);

            return true;
        }

        bool CAudioWav::readMemorySamples(CAudioSource* source, ALuint bufferId, char* lpBuffer, long nBytes)
        {
            u32 size = 0;

            finished = false;

            u32 sBufferSize = source->getBufferSize();
            c8* sBuffer = source->getBuffer();

            bufferthis(&bufferId, lpBuffer, nBytes);

            if (alGetError() != AL_NO_ERROR)
            {
                return false;
            }

            return true;
        }

        bool CAudioWav::hasFinished() const
        {
            return finished;
        }
    }
}
#endif

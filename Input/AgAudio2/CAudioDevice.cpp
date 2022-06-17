#include "../../config.h"
#ifdef AgAudio2
#include "CAudioDevice.h"
#include <string>
#include <fstream>
#include <assert.h>
#include <memory.h>
//#include <stdint.h>
//#include <stdlib.h>
#include <iostream>
//#include <stdint.h>
//#include <unistd.h>
//#include <math.h>
#include <cstring>
#include <type_traits>
#include <vector>


using namespace std;


unsigned int aVal = 0x11223344;
char* myValReadBack = (char*)(&aVal);
std::int32_t convert_to_int(char* buffer, std::size_t len)
{
    //if (*myValReadBack == 0x11) printf("Big endian\r\n");
    //else                       printf("Little endian\r\n");

    std::int32_t a = 0;
    if (*myValReadBack != 0x11)
        std::memcpy(&a, buffer, len);
    else
        for (std::size_t i = 0; i < len; ++i)
            reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
    return a;
}

bool load_wav_file_header(std::ifstream& file,
    std::uint8_t& channels,
    std::int32_t& sampleRate,
    std::uint8_t& bitsPerSample,
    ALsizei& size)
{
    char buffer[4];
    if (!file.is_open())
        return false;

    // the RIFF
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read RIFF" << std::endl;
        return false;
    }
    if (std::strncmp(buffer, "RIFF", 4) != 0)
    {
        std::cerr << "ERROR: file is not a valid WAVE file (header doesn't begin with RIFF)" << std::endl;
        return false;
    }

    // the size of the file
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read size of file" << std::endl;
        return false;
    }

    // the WAVE
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read WAVE" << std::endl;
        return false;
    }
    if (std::strncmp(buffer, "WAVE", 4) != 0)
    {
        std::cerr << "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)" << std::endl;
        return false;
    }

    // "fmt/0"
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read fmt/0" << std::endl;
        return false;
    }

    // this is always 16, the size of the fmt data chunk
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read the 16" << std::endl;
        return false;
    }

    // PCM should be 1?
    if (!file.read(buffer, 2))
    {
        std::cerr << "ERROR: could not read PCM" << std::endl;
        return false;
    }

    // the number of channels
    if (!file.read(buffer, 2))
    {
        std::cerr << "ERROR: could not read number of channels" << std::endl;
        return false;
    }
    channels = convert_to_int(buffer, 2);

    // sample rate
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read sample rate" << std::endl;
        return false;
    }
    sampleRate = convert_to_int(buffer, 4);

    // (sampleRate * bitsPerSample * channels) / 8
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read (sampleRate * bitsPerSample * channels) / 8" << std::endl;
        return false;
    }

    // ?? dafaq
    if (!file.read(buffer, 2))
    {
        std::cerr << "ERROR: could not read dafaq" << std::endl;
        return false;
    }

    // bitsPerSample
    if (!file.read(buffer, 2))
    {
        std::cerr << "ERROR: could not read bits per sample" << std::endl;
        return false;
    }
    bitsPerSample = convert_to_int(buffer, 2);

    // data chunk header "data"
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read data chunk header" << std::endl;
        return false;
    }
    if (std::strncmp(buffer, "data", 4) != 0)
    {
        std::cerr << "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)" << std::endl;
        return false;
    }

    // size of data
    if (!file.read(buffer, 4))
    {
        std::cerr << "ERROR: could not read data size" << std::endl;
        return false;
    }
    size = convert_to_int(buffer, 4);

    /* cannot be at the end of file */
    if (file.eof())
    {
        std::cerr << "ERROR: reached EOF on the file" << std::endl;
        return false;
    }
    if (file.fail())
    {
        std::cerr << "ERROR: fail state set on the file" << std::endl;
        return false;
    }

    return true;
}



char* load_wav(const std::string& filename,
    std::uint8_t& channels,
    std::int32_t& sampleRate,
    std::uint8_t& bitsPerSample,
    ALsizei& size)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open())
    {
      //  std::cerr << "ERROR: Could not open \"" << filename << "\"" << std::endl;
        return nullptr;
    }
    if (!load_wav_file_header(in, channels, sampleRate, bitsPerSample, size))
    {
      //  std::cerr << "ERROR: Could not load wav header of \"" << filename << "\"" << std::endl;
        return nullptr;
    }

    char* data = new char[size];

    in.read(data, size);

    return data;
}


namespace agEngine
{
    namespace audio
    {
        CAudioDevice::CAudioDevice()
        : active(true), sourceCount(1)
        {
            if (!(sDevice = alcOpenDevice(NULL)))
            {
                active = false;
            }

            sContext = alcCreateContext(sDevice, NULL);
            alcMakeContextCurrent(sContext);

            ALfloat orient[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
            alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
            alListenerfv(AL_ORIENTATION, orient);
            alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);

            // Clear the error stack
            alGetError();
        }

        CAudioDevice::~CAudioDevice()
        {
            clear();
        }

        CAudioSource* CAudioDevice::createAudioSource(CAudioStream* stream)
        {
            CAudioSource* nSrc = new CAudioSource(this, stream);
            nSrc->setSourceId(sourceCount);
            ++sourceCount;
            sources.push_back(nSrc);
            return nSrc;
        }

        void CAudioDevice::addAudioSource(CAudioSource* newSource)
        {
            newSource->setSourceId(sourceCount);
            ++sourceCount;
            sources.push_back(newSource);
            newSource->grab();
        }

        CAudioStream* CAudioDevice::createAudioStream(const c8* filename, bool loadToMemory)
        {
            #ifdef OGG
            // need to write a clause for different file types in the future
            CAudioData* audioData = new CAudioOgg(filename, loadToMemory);
            CAudioStream* audStream = new CAudioStream(audioData);
            return audStream;
            #endif
        }

        void CAudioDevice::playAll()
        {
            for (u32 i = 0; i < sources.size(); ++i)
                sources[i]->updateBuffer(false);
        }

        void CAudioDevice::clear()
        {
            for (u32 i = 0; i < sources.size(); ++i)
                sources[i]->drop();

            sources.clear();
        }

        u32 CAudioDevice::getNextAvailableSourceId()
        {
            u32 temp = sourceCount;
            ++sourceCount;
            return temp;
        }

        void CAudioDevice::setListenerPosition(const core::vector3d<float>& newPosition)
        {
            alListener3f(AL_POSITION, newPosition.X, newPosition.Y, newPosition.Z);
        }

        void CAudioDevice::setListenerVelocity(const core::vector3d<float>& newVelocity)
        {
            alListener3f(AL_VELOCITY, newVelocity.X, newVelocity.Y, newVelocity.Z);
        }

        void CAudioDevice::setListenerOrientation(const core::vector3d<float>& orient1, const core::vector3d<float>& orient2)
        {
            ALfloat orient[] = {orient1.X, orient1.Y, orient1.Z, orient2.X, orient2.Y, orient2.Z};
            alListenerfv(AL_ORIENTATION, orient);
        }
    }
}
#endif

// minimp3 example player application for Win32
// this file is public domain -- do with it whatever you want!
#define MAIN_PROGRAM

#include <iostream>

#include "libc.h"
#include "minimp3.h"

#include "./AgAudio3/CAudioDevice.h"

using namespace std;

#define BUFFER_COUNT 2

static mp3_decoder_t* mp3;
static mp3_info_t info;
static unsigned char* stream_pos;
static long bytes_left;
static int byte_count;
static signed short sample_buffer[MP3_MAX_SAMPLES_PER_FRAME * BUFFER_COUNT];

int main(void) {
    char input_file_name[] = "001.mp3";
    HANDLE hFile, hMap;

    agEngine::audio::CAudioDevice* adevice = new agEngine::audio::CAudioDevice();
    agEngine::audio::CAudioSource* test = adevice->createAudioSource(adevice->createAudioStream("./cAudioTheme1.ogg", 1));

    // open and mmap() the file
    hFile = CreateFile(input_file_name, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    long nTotalFileBytes = GetFileSize(hFile, NULL) - 128;
    hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    stream_pos = (unsigned char*)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);

    // set up minimp3 and decode the first frame
    mp3 = mp3_create();

    int offset = 0;
    long Total_Count = 0;
    bytes_left = nTotalFileBytes;
    while (true)
    {
        byte_count = mp3_decode(mp3, stream_pos + offset, bytes_left, sample_buffer, &info);
        if (!byte_count)
            break;
        Total_Count += MP3_MAX_SAMPLES_PER_FRAME * BUFFER_COUNT;
        bytes_left -= byte_count;
        offset += byte_count;
    }

    char* pcm_buffer = new char[Total_Count];
    offset = 0;
    int buffer_offset = 0;
    bytes_left = nTotalFileBytes;
    while (true)
    {
        byte_count = mp3_decode(mp3, stream_pos + offset, bytes_left, sample_buffer, &info);
        if (!byte_count)
            break;
        memcpy(pcm_buffer + buffer_offset, sample_buffer, MP3_MAX_SAMPLES_PER_FRAME * BUFFER_COUNT);
        buffer_offset += MP3_MAX_SAMPLES_PER_FRAME * BUFFER_COUNT;
        bytes_left -= byte_count;
        offset += byte_count;
    }

    while (true)
    {
        if (!test->isPlaying())
            test->playFirstBuffer(pcm_buffer, Total_Count);
        else
            adevice->playBuffer(pcm_buffer, Total_Count);
    }

    delete pcm_buffer;

    // endless loop
    while (1) Sleep(10);

    return 0;
}

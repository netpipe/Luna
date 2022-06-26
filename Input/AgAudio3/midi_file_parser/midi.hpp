#pragma once

#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>


class Midi {
private:
    uint32_t readBytes(uint16_t);
    uint8_t readByte();
    void seekg(int32_t);
    uint32_t readVarLen();
    std::string readStr(uint16_t);
    uint32_t swap32(uint32_t) const;
    uint16_t swap16(uint16_t) const;

    std::ifstream in;
    uint32_t pos; // file
    float unitOfTime;

    struct Track {
        struct Note {
            bool state;
            uint8_t channel;
            int8_t key, velocity;
            uint32_t startTick, durationTick;
            float startTime, durationTime;
        };
        std::vector<Note> notes;
    };
    std::vector<Track> tracks;

    struct Tempo {
        uint32_t tick, tempo;
        float time;
    };
    std::vector<Tempo> tempo_map;
public:
    Midi();
    ~Midi();
    bool parse(const char*);
    const std::vector<Track>& getTracks() const;
    void setUnitOfTime(float);
    float getUnitOfTime() const;
};

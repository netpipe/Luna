#include "midi.hpp"

Midi::Midi() : pos(0), unitOfTime(60000.0f) {}

Midi::~Midi(){
    tracks.clear();
}

bool Midi::parse(const char *name) {
    in.open(name, std::ios::in | std::ios::binary);
    if (!in.is_open()) return 1;

    if (readStr(4).compare("MThd") != 0) return 1;

    uint32_t chunkSize = readBytes(4);
    if (chunkSize != 6) return 1;

    //uint16_t formatType = readBytes(2);
    seekg(2);

    uint16_t numOfTracks = readBytes(2);
    uint32_t timeDivision = readBytes(2);

    if (timeDivision & 0x8000) 
        return 1; //15 bit set SMPTE format

    uint8_t previousEvent = 0;
    uint32_t maxTicks = 0;

    for (uint16_t i = 0; i < numOfTracks; ++i) {
        //bool EOT = false;
        //std::string mtrkHeader = readStr(4);
        seekg(4); // MTrk header
        uint32_t length = pos + readBytes(4);
        //seekg(8); // Mtrk header 4 + trackLength 4
        uint32_t tick = 0;
        tracks.push_back(Track());
        for (;pos <= length/*!EOT*/;) {
            tick += readVarLen();
            uint8_t event = readByte();

            if (event < 0x80) {
                event = previousEvent;
                seekg(-1);
                if(event == 0) continue; // SysEx event
            } else 
                previousEvent = ((event & 0xF0) != 0xF0) ? event : 0;
            

            switch(event & 0xF0) {
                case 0x80: { // note off
                    int8_t note = readByte();
                    int8_t velocity = readByte();
                    tracks.back().notes.push_back({.state=false, .channel=(uint8_t)(event & 0xF), 
                        .key = note, .velocity = velocity, .startTick = tick});
                }
                break;

                case 0x90: { // note on
                    int8_t note = readByte();
                    int8_t velocity = readByte();
                         
                    tracks.back().notes.push_back({.state=(bool)velocity, .channel=(uint8_t)(event & 0xF), 
                        .key = note, .velocity = velocity, .startTick = tick});      
                }
                break;

                case 0xA0: { //Polyphonic Pressure
                    //int8_t note = readByte();
                    //int8_t pressure = readByte();   
                    seekg(2);
                }
                break;

                case 0xB0: { // controller
                    //int8_t controller = readByte();
                    //int8_t value = readByte();  
                    seekg(2);
                }
                break;

                case 0xC0: { // program change
                    //int8_t program = readByte();
                    seekg(1);
                }
                break;

                case 0xD0: { // Channel Pressure
                    //int8_t pressure = readByte();
                    seekg(1);
                }
                break;

                case 0xE0: { // pitch bend
                    //int8_t lsb = readByte();
                    //int8_t msb = readByte();
                    seekg(2);
                }
                break;

                case 0xF0: { // SysEx event
                    if (event == 0xF0) // System Exclusive Message Begin
                        seekg(readVarLen());
                    else if (event == 0xF7) // System Exclusive Message End
                        seekg(readVarLen());
                    else if (event == 0xFF) {
                        uint8_t type = readByte();
                        uint32_t value = readVarLen();

                        switch(type) {
                            case 0x00: { // MetaSequence
                                seekg(2);
                            }
                            break;

                            case 0x01: { // MetaText
                                seekg(value);
                            }
                            break;

                            case 0x02: { // MetaCopyright
                                seekg(value);
                            }
                            break;

                            case 0x03: { // MetaTrackName
                                seekg(value);
                            }
                            break;

                            case 0x04: { // MetaInstrumentName
                                seekg(value);
                            }
                            break;

                            case 0x05: { // MetaLyrics
                                seekg(value);
                            }
                            break;

                            case 0x06: { // MetaMarker
                                seekg(value);
                            }
                            break;

                            case 0x07: { // MetaCuePoint
                                seekg(value);
                            }
                            break;

                            case 0x20: { // MetaChannelPrefix
                                seekg(1);
                            }
                            break;

                            case 0x2F: { // END OF TRACK
                                //EOT = true;
                            }
                            break;

                            case 0x51: { // MetaSetTempo
                                const uint32_t BPM = 60000000 / readBytes(3);
                                tempo_map.push_back({tick, BPM});
                            }
                            break;

                            case 0x54: { // MetaSMPTEOffset
                               seekg(5);
                            }
                            break;

                            case 0x58: { // MetaTimeSignature
                                //uint8_t numenator = readByte();
                                //uint8_t denominator = readByte();
                                //seekg(2);
                                seekg(4);
                                
                                //std::cout << "time signature" << (uint16_t)numenator << "/" << (uint32_t)(1 <<  denominator) << std::endl;
                            }
                            break;

                            case 0x59: { // MetaKeySignature
                                seekg(2);
                            }
                            break;

                            case 0x7F: { // MetaSequencerSpecific
                                seekg(value);
                            }
                            break;

                            default:break;
                        }
                    }
                }
                break;

                default:break;
            }
        }
        
        if (tick > maxTicks)
            maxTicks = tick; 
        
    }   

    std::sort(tempo_map.begin(), tempo_map.end(), [&](const Tempo &tempo1, const Tempo &tempo2) {
        return tempo1.tick < tempo2.tick;
    });

    for (float i = 0, elapsedTicks = 0.0f, time = 0.0f; i < tempo_map.size(); ++i) {
        time += (unitOfTime / tempo_map[i ? i - 1 : i].tempo) * ((tempo_map[i].tick - elapsedTicks) / timeDivision);
        elapsedTicks = tempo_map[i].tick;
        tempo_map[i].time = time;
    }

    //float maxTime = 0;

    for (auto& track : tracks)
        for (auto& note : track.notes) 
            if(note.state == true) {
                auto noteOff = std::find_if(track.notes.begin(), track.notes.end(), [&](const Track::Note &foundNote){ 
                    return (bool)((note.key == foundNote.key) && 
                        (note.channel == foundNote.channel) && foundNote.state == false);
                });

                if (noteOff != track.notes.end()) {
                    auto tempo = std::find_if(tempo_map.begin(), tempo_map.end(), [&](const Tempo &bpm) {
                        return (note.startTick < bpm.tick);
                    }) - 1;

                    if (tempo != tempo_map.end()) {
                        const float TEMPO = ((unitOfTime / tempo->tempo) /  timeDivision);
                        note.durationTick = (noteOff->startTick - note.startTick);
                        note.durationTime = note.durationTick * TEMPO;
                        note.startTime = tempo->time + ((note.startTick - tempo->tick) * TEMPO);
                        track.notes.erase(noteOff);
                        /*
                        if (note.startTime > maxTime)
                            maxTime = note.startTime;
                        */
                    }
                }
            }
        
    //maxTime = tempo_map.back().time + (maxTicks - tempo_map.back().tick) * (unitOfTime / tempo_map.back().tempo) / timeDivision;
    //std::cout << "minutes " << ((uint32_t)maxTime / 1000) / 60 << " seconds " << ((uint32_t)maxTime / 1000) % 60 << std::endl;
    in.close();
    return 0;
}

const std::vector<Midi::Track>& Midi::getTracks() const {
    return tracks;
}

void Midi::setUnitOfTime(float unit) {
    unitOfTime = unit;
}

float Midi::getUnitOfTime() const {
    return unitOfTime;
}

uint32_t Midi::readBytes(uint16_t length) {
    uint32_t value = 0;
    for (uint8_t i = 0; i < length; ++i)
        value = (value << 8) | readByte();
    return value;
}

uint8_t Midi::readByte() {
    ++pos;
    return in.get();
}

void Midi::seekg(int32_t cursor) {
    pos += cursor;
    //in.seekg(pos, std::ios::beg);
    in.seekg(cursor, std::ios::cur);
}

std::string Midi::readStr(uint16_t length) {
    std::string str = "";
    for (uint16_t i = 0; i < length; ++i)
        str += readByte();
    return str;
}

uint32_t Midi::readVarLen() {
    uint32_t value = readByte();
    uint8_t byteRead = 0;
    if (value & 0x80) {
        value &= 0x7F;
         do {
            byteRead = readByte();
            value = (value << 7) | (byteRead & 0x7F);
         } while (byteRead & 0x80);
    }
    return value;
}

uint32_t Midi::swap32(uint32_t dword) const {
    return ((dword>>24)&0xff) | ((dword<<8)&0xff0000) | 
        ((dword>>8)&0xff00) | ((dword<<24)&0xff000000);
}

uint16_t Midi::swap16(uint16_t word) const {
    return ((word >> 8) | (word << 8));
}

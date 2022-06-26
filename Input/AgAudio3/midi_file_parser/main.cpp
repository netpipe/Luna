#include <cmath>
#include "midi.hpp"
double noteFrequency(int8_t note) {
    return (pow(2, (note - 69) / 12)) * 440;
}
int main() {
    Midi midi;
    midi.setUnitOfTime(60000.0f); // milliseconds
    midi.parse("file.mid");
    const char* names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    for (auto &track : midi.getTracks()) 
        for (auto &note : track.notes) 
            std::cout << 
                "channel " << (uint16_t)note.channel << 
                " note " << (uint32_t)note.key << 
                " note name " << names[note.key%12] << (uint16_t)(note.key / 12) - 1 << 
                " note frequency " << noteFrequency(note.key) <<
                " start tick " << note.startTick << 
                " start time " << (uint32_t)note.startTime << 
                " duration ticks " << note.durationTick <<
                " duration time " << note.durationTime 
            << std::endl;

    
	return 0;
}

//
// Created by TPNml on 9/26/2023.
//

#include "phSpace.h"

using namespace phSpace;

Note::Note(int midiNumber, int time) {
    this->midiNumber = midiNumber;
    this->time = time;
}

Note::Note(std::string note_name, std::string octave, std::string accidental, std::string duration, int prev_duration) {
    this->midiNumber = xml_parsing::getMidiNumber(note_name, octave, accidental);
    this->time = std::stoi(duration) - prev_duration;
}

std::string Note::toString() {
    return std::format("Note({} @ {})", midiNumber, time);
}
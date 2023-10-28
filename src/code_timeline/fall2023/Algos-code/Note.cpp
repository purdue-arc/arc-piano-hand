//
// Created by TPNml on 9/26/2023.
//

#include "phSpace.h"

using namespace phSpace;

Note::Note(int midiNumber, int time) {
    this->midiNumber = midiNumber;
    this->time = time;
}

std::string Note::toString() {
    return std::format("Note({} @ {})", midiNumber, time);
}
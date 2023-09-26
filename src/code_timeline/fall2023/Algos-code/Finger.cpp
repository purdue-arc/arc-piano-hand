//
// Created by TPNml on 9/26/2023.
//

#include "phSpace.h"
using namespace phSpace;

Finger::Finger() {
    this->state = -1;
    this->midi = -1;
    this->currentNote = nullptr;
}

void Finger::playNote(Note note) {
}

void Finger::releaseNote() {
}

void Finger::moveTo(int midi) {
}



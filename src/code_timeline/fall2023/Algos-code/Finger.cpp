//
// Created by TPNml on 9/26/2023.
//

#include "phSpace.h"
using namespace phSpace;

Finger::Finger(int id) {
    this->id = id;
    this->state = -1;
    this->midi = -1;
    this->currentNote = nullptr;
}

void Finger::playNote(Note *note) {
    if (currentNote != nullptr) {
        throw std::runtime_error("Tried to allocate finger " + std::to_string(id) +
                                      " onto note while it was playing");
    }
    currentNote = note;
}

void Finger::releaseNote() {
    currentNote = nullptr;
}

void Finger::moveTo(int midi) {
    // to define...
}



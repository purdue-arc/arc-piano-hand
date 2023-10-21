//
// Created by TPNml on 9/26/2023.
//

#include "phSpace.h"
using namespace phSpace;

Finger::Finger(int id) {
    this->id = id;
    this->state = false; // Initialized to false as no finger is playing any note when initially declared
    this->currentNote = nullptr;
}

int Finger::getID() {
    return id;
}

Note * Finger::getNote() {
    return this->currentNote;
}

bool Finger::isPlaying() {
    return state;
}

void Finger::playNote(Note *note) {
    if (currentNote != nullptr) {
        throw std::runtime_error("Tried to allocate finger " + std::to_string(id) +
                                      " onto note while it was playing");
    }
    currentNote = note;
    state = true; // The finger is being used to play a note
}

void Finger::releaseNote() {
    currentNote = nullptr;
    state = false; // stop finger from playing note
}

void Finger::moveTo(Note * note) {
    // to define...
}



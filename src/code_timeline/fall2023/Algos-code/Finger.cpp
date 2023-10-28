//
// Created by TPNml on 9/26/2023.
//

#include "phSpace.h"
using namespace phSpace;

Finger::Finger(int id) {
    this->id = id;
    this->position_on_hand = (3*id) - 5;
    this->state = false; // Initialized to false as no finger is playing any note when initially declared
    this->currentNote = nullptr;
}

Finger::Finger(int id, int position_on_hand) {
    this->id = id;
    this->position_on_hand = position_on_hand;
    this->state = false; // Initialized to false as no finger is playing any note when initially declared
    this->currentNote = nullptr;
}

int Finger::getPositionOnHand() {
    return this->position_on_hand;
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

std::string Finger::toString() {
    if (currentNote == nullptr) {
        return std::format("Finger(id={}, not playing )", this->id);
    }
    return std::format("Finger(id={}, {})", this->id, this->currentNote->toString());
}

void Finger::setState(bool state) {
    this->state = state;
}



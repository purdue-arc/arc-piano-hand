//
// Created by TPNml on 9/26/2023.
//

#include "phSpace.h"
using namespace phSpace;

Hand::Hand(int start_position, int hand_type) {
    this->midi_position = start_position;
    if (hand_type == NORMAL_HAND) {
        for (int i = 0; i < 4; i++) {
            auto *f = new Finger(i);
            this->fingers.push_back(f);
        }
    }
}

void Hand::moveHandTo(int midi) {
}

void Hand::playNoteOnHand(Note note) {

}

void Hand::release() {
    for (Finger *f : fingers) {
        f->releaseNote();
    }
}

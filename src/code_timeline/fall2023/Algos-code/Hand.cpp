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

int Hand::num_fingers() {
    return this->fingers.size();
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

int hand_cost(Hand h1, Hand h2) {
    if (h1.num_fingers() != h2.num_fingers()) {
        return INT_MAX;
    }
    int cost = 0;
    for (auto i = 0; i < h1.num_fingers(); i++) {
        int a = h1.fingers[i]->getNote();
        if (a == NULL_NOTE) {
            continue;
        }
        int b = h2.fingers[i]->getNote();
        if (b == NULL_NOTE) {
            continue;
        }
        cost += (b - a)*(b - a);
    }
    return cost;
}

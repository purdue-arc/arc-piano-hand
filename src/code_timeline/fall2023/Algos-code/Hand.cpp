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

void Hand::release() {
    for (Finger *f : fingers) {
        f->releaseNote();
    }
}

int hand_cost(Hand h1, Hand h2) {
    // Assume fingers are sorted from least to greatest id in array
    if (h1.num_fingers() != h2.num_fingers()) {
        return INT_MAX;
    }
    int cost = 0;
    for (auto i = 0; i < h1.num_fingers(); i++) {
        if (!h1.fingers[i]->isPlaying()) {
            continue;
        }
        int a = h1.fingers[i]->getNote()->midiNumber;
        if (!h2.fingers[i]->isPlaying()) {
            continue;
        }
        int b = h1.fingers[i]->getNote()->midiNumber;
        cost += (b - a)*(b - a);
    }
    return cost;
}

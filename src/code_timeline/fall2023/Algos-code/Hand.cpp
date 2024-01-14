//
// Created by TPNml on 9/26/2023.
//

#include "phSpace.h"

using namespace phSpace;

Hand::Hand(int start_position, int hand_type) {
    this->midi_position = start_position;
    this->hand_type = hand_type;
    if (hand_type == NORMAL_HAND) {
        for (int i = 0; i < 4; i++) {
            auto *f = new Finger(i, (3 * i) - 5, 6);
            this->fingers.push_back(f);
        }
    }
    if (hand_type == BAD_HAND) {
        for (int i = 0; i < 3; i++) {
            auto *f = new Finger(i, (3 * i) - 3, 6);
            this->fingers.push_back(f);
        }
    }
}

// Make a copy of a Hand object
Hand *Hand::copy() {
    Hand *h = new Hand(this->midi_position, this->hand_type);
    for (int i = 0; i < this->fingers.size(); i++) {
        if (this->fingers[i]->isPlaying()) {
            h->fingers[i]->playNote(this->fingers[i]->getNote());
        }
    }
    return h;
}

int Hand::num_fingers() {
    return this->fingers.size();
}

// Release all fingers on the Hand
void Hand::release() {
    for (Finger *f: fingers) {
        f->releaseNote();
    }
}

// Return the Viterbi cost between two hand configurations (unused)
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
        cost += (b - a) * (b - a);
    }
    return cost;
}

std::string Hand::toString() {
    std::string output = std::format("Hand(midi_position={}, <", this->midi_position);
    for (Finger *finger: this->fingers) {
        output.append(finger->toString());
        output.append(", ");
    }
    output.append(">)");
    return output;
}

// Basically toString but slightly different
std::string Hand::getOutputFromViterbi(std::vector<Hand *> h) {
    std::string output;
    for (Hand *hand: h) {
        output.append(hand->toString());
        output.append("\n");
    }
    return output;
}
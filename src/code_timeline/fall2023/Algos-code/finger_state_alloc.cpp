//
// Created by inner-LMNt (Kevin Huang) on 10/7/2023.
//

#include "phSpace.h"
using namespace phSpace;

void alloc_step(std::vector<Hand *> *list, Hand* existing, std::vector<Note *> toPlay, int start_finger) {
    if (toPlay.empty()) {
        list->push_back(existing->copy());
        return;
    }
    for (int k = start_finger; k < existing->num_fingers(); k++) {
        Finger *f = existing->fingers[k];
        if (!(f->isPlaying())) {
            for (Note *i: toPlay) {
                f->playNote(i);
                Note *i_copy = i;
                auto it = std::find(toPlay.begin(), toPlay.end(), i);
                toPlay.erase(it);
                alloc_step(list, existing, toPlay, k);
                toPlay.insert(it, i_copy);
                f->releaseNote();
            }
        }
    }
}

std::vector<Hand *> finger_state_alloc::allocate_finger_state(int hand_type, std::vector<Note *> toPlay) {
    std::vector<Hand *> list{};
    alloc_step(&list, new Hand(60, hand_type), toPlay, 0);
    return list;
}


int main_test () {
    std::vector<Note *> toPlay = {new Note (1, 0), new Note (3, 0)};

    std::vector<Hand *> hands = finger_state_alloc::allocate_finger_state(NORMAL_HAND, toPlay);

    for (Hand* h : hands) {
        std::cout << "Hand: ";
        for (Finger *f : h->fingers) {
            std::cout << f->getNote() << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
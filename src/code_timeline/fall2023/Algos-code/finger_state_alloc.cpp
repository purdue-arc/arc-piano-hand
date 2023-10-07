//
// Created by inner-LMNt (Kevin Huang) on 10/7/2023.
//

#include "phSpace.h"
using namespace phSpace;

std::vector<Hand> allocate_finger_state(std::vector<Hand> list, Hand existing, std::vector<Note> toPlay) {
    if (toPlay.empty()) {
        list.push_back(existing);
        return list;
    }
    Note note = toPlay[0];
    toPlay.erase(toPlay.begin());

    for (Finger *f : existing.fingers) {
        if (!f->isPlaying()) {
            f->playNote(&note);
            list = allocate_finger_state(list, existing, toPlay);
            f->releaseNote();
        }
    }
    return list;
}

int main () {
    std::vector<Note> toPlay = {Note (1, 0), Note (3, 0)};

    std::vector<Hand> list;

    Hand h1 = Hand(0, NORMAL_HAND);

    list = allocate_finger_state(list, h1, toPlay);

    for (Hand h : list) {
        std::cout << "Hand: ";
        for (Finger *f : h.fingers) {
            std::cout << f->getNote() << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
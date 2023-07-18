#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

static double stretch(Finger *f1, Finger *f2) {
    return abs(f2->getNoteCurrentlyBeingPlayed().get_midi_note_value() - f1->getNoteCurrentlyBeingPlayed().get_midi_note_value());
}

static double vertical_cost(FingerState *fs) {
    // Rewrite function
    return 0.0;
}

static double horizontal_cost(FingerState *fs) {
    double cost = 0.0;
    for (int i = 0; i < fs->getSize(); i++) {
        Finger *f1 = fs->get(i);
        if (f1->isNoteBeingPlayed()) {
            for (int j = 0; j < i; i++) {
                Finger *f2 = fs->get(j);
                if (f2->isNoteBeingPlayed()) {
                    cost += sqrt(stretch(f1, f2));
                }
            }
        }
    }
    return cost;
}

static double finger_range_cost_hand(FingerState *fs) {
    std::unordered_map<std::vector<int>, std::vector<int>> ranges = {
        {{0, 1}, {-5, 10}},
        {{0, 2}, {-4, 12}},
        {{0, 3}, {-3, 14}},
        {{0, 4}, {-1, 15}},
        {{1, 2}, {1, 5}},
        {{1, 3}, {1, 7}},
        {{1, 4}, {2, 10}},
        {{2, 3}, {1, 4}},
        {{2, 4}, {1, 7}},
        {{3, 4}, {1, 5}}
    };
    double cost = 0.0;
    for (int i = 0; i < fs->getSize(); i++) {
        Finger *f1 = fs->get(i);
        if (f1->isNoteBeingPlayed()) {
            for (int j = 0; j < i; i++) {
                Finger *f2 = fs->get(j);
                if (f2->isNoteBeingPlayed() && (f2->getID() != f1->getID())) {
                    std::vector<int> key{f1->getID(), f2->getID()};
                    int stretch_val = stretch(f1, f2);
                    std::vector<int> range = ranges.at(key);
                    if (stretch_val < range[0]) {
                        cost += 10 * (range[0] - stretch_val);
                    }
                    else if (stretch_val > range[1]) {
                        cost += 10 * (range[1] - stretch_val);
                    }
                }
            }
        }
    }
    return cost;
}

static double aggregate_cost(FingerState *fs_curr, FingerState *fs_next) {
    assert(fs_curr != nullptr);
    double weights[3] = { 1.0, 1.0, 1.0 };
    double cost = 0;
    cost += weights[0] * vertical_cost(fs_curr) + weights[1] * horizontal_cost(fs_curr) + weights[2] * finger_range_cost_hand(fs_curr);
    return cost;
}
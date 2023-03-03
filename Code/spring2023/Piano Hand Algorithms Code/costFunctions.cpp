#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

double vertical_cost(FingerState fs) {
    double cost = 0.0;
    for (Finger f1 : fs.getFingers()) {
        for (Finger f2 : fs.getFingers()) {
            if (f2.getID() != f1.getID()) {
                cost += sqrt(abs(f2.getNoteCurrentlyBeingPlayed().get_midi_note_value() - f1.getNoteCurrentlyBeingPlayed().get_midi_note_value()));
            }  
        }
    }
    return cost;
}

double horizontal_cost(FingerState fs) {
    double cost = 0.0;
    for (Finger f1 : fs.getFingers()) {
        for (Finger f2 : fs.getFingers()) {
            if (f2.getID() != f1.getID()) {
                int stretch = 0;
                if (f2.getID() > f1.getID()) {
                    stretch = f2.getNoteCurrentlyBeingPlayed().get_midi_note_value() - f1.getNoteCurrentlyBeingPlayed().get_midi_note_value();
                } else {
                    stretch = f1.getNoteCurrentlyBeingPlayed().get_midi_note_value() - f2.getNoteCurrentlyBeingPlayed().get_midi_note_value();
                }
                cost += sqrt(stretch);
            }  
        }
    }
    return cost;
}

double finger_range_cost_hand(FingerState fs) {
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
    for (Finger f1 : fs.getFingers()) {
        if (f1.isNoteBeingPlayed()) {
            for (Finger f2 : fs.getFingers()) {
                if (f2.isNoteBeingPlayed() && (f2.getID() != f1.getID())) {
                    std::vector<int> key{f1.getID(), f2.getID()};
                    int stretch = 0;
                    if (f2.getID() > f1.getID()) {
                        stretch = f2.getNoteCurrentlyBeingPlayed().get_midi_note_value() - f1.getNoteCurrentlyBeingPlayed().get_midi_note_value();
                    } else {
                        stretch = f1.getNoteCurrentlyBeingPlayed().get_midi_note_value() - f2.getNoteCurrentlyBeingPlayed().get_midi_note_value();
                    }
                    std::vector<int> range = ranges.at(key);
                    if (stretch < range[0]) {
                        cost += 10 * (range[0] - stretch);
                    }
                    else if (stretch > range[1]) {
                        cost += 10 * (range[1] - stretch);
                    }
                }
            }
        }
    }
    return cost;
}

double aggregate_cost(FingerState fs) {
    double weights[3] = { 1.0, 1.0, 1.0 };
    double cost = 0;
    cost += weights[0] * vertical_cost(fs) + weights[1] * horizontal_cost(fs) + weights[2] * finger_range_cost_hand(fs);
    return cost;
}
//
// Created by TPNml on 10/28/2023.
//

#include "phSpace.h"

using namespace phSpace;

std::vector<std::vector<Note *>> input_output::readNotes() {
    // dummy notes
    std::vector<std::vector<Note *>> toReturn{};
    for (int i = 0; i < 4; i++) {
        std::vector<Note *> notes{};
        notes.push_back(new Note(57 + i, i));
        toReturn.push_back(notes);
        std::vector<Note *> notes2{};
        notes2.push_back(new Note(57 + 7 - i, i));
        toReturn.push_back(notes2);
    }
    return toReturn;
}
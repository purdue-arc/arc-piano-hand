//
// Created by TPNml on 10/28/2023.
//

#include "phSpace.h"

using namespace phSpace;

std::vector<std::vector<Note *>> input_output::readNotes() {
    // dummy notes
    std::vector<std::vector<Note *>> toReturn{};
    for (int i = 0; i < 8; i++) {
        std::vector<Note *> notes{};
        notes.push_back(new Note(60 + i, i));
        notes.push_back(new Note(60 + i + 1, i));
        toReturn.push_back(notes);
    }
    return toReturn;
}
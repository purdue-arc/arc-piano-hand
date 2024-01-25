//
// Created by TPNml on 10/28/2023.
//

#include "phSpace.h"
using namespace phSpace;

// Takes in file path in first line of function and returns vector<vector<Note *>> of the Notes, organized as follows:
// Note group 1 {
//      Note 1;
//      Note 2;
//      ...
// };
// Note group 2 {
//      ...
// };
// ...
std::vector<std::vector<Note *>> input_output::readNotes() {
    rapidxml::file<> xmlFile("C:\\Users\\TPNml\\CLionProjects\\Algos-code\\hotcrossmasked.musicxml");
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<> *title = doc.first_node();

    std::vector<Note *> notes_io = xml_parsing::find_notes(title);

    std::vector<std::vector<Note *>> toReturn{};

    // dummy notes

    for (Note * note : notes_io) {
        std::vector<Note *> notes{};
        notes.push_back(note);
        toReturn.push_back(notes);
    }
    return toReturn;
}
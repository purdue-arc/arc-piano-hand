#include "rapidxml_utils.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "phSpace.h"

using namespace phSpace;

void print_notes(rapidxml::xml_node<> *node) {
    for (node = node->first_node(); node != NULL; node = node->next_sibling()) {
        if (node->type() == rapidxml::node_element) //check node type
        {
            std::string x = node->value();
           std::cout << node->name() << ": " << x << std::endl;
           print_notes(node);
        }
    }
}

// Allows you to send nodes for
void handlenode(rapidxml::xml_node<> *node, std::string x) {
    for (node = node->first_node(); node != NULL; node = node->next_sibling()) {
        if (node->type() == rapidxml::node_element) //check node type
        {
            if (x == node->name()) {
                std::cout << node->name() << ": " << node->value() << std::endl;
                print_notes(node);
                std::cout << std::endl;
            }
            handlenode(node, x);
        }
    }
}

// Allows you to send nodes for
rapidxml::xml_node<> *search_for_node(rapidxml::xml_node<> *node, std::string x) {
    for (node = node->first_node(); node != NULL; node = node->next_sibling()) {
        if (node->type() == rapidxml::node_element) //check node type
        {
            if (x == node->name()) {
               return node;
            }
            handlenode(node, x);
        }
    }
    return nullptr;
}

Note * parse_note(rapidxml::xml_node<> *node) { // Node is the root of the tree where the note is
    // Parse the tree and find the tag with the step
    // Alter
    // Octave
    // And duration
    // Store each of these in a variable
    // You can use the search_for_node function above which searches for a given tag in the tree
    std::string note_name = search_for_node(node, "name")->value();
    std::string octave = search_for_node(node, "octave")->value();
    std::string alter = search_for_node(node, "alter")->value();
    std::string duration = search_for_node(node, "duration")->value();

    // Then call the Note constructor with these values and return the resulting Note
    Note *parsedNote = new Note(note_name, octave, alter, duration, 0);
    return parsedNote;
}

std::vector<Note *> find_notes(rapidxml::xml_node<> *node) {
    std::vector<Note *> notes{};
    for (node = node->first_node(); node != NULL; node = node->next_sibling()) {
        if (node->type() == rapidxml::node_element) //check node type
        {
            if ("note" == node->name()) {
               notes.push_back(parse_note(node)); //add to the end
            }
            find_notes(node);
        }
    }
    return notes;
}


int xml_parsing::getMidiNumber(std::string noteName, std::string octave, std::string alter) {
    int midiNumber = 0;
    int octave_num = std::stoi(octave);
    char noteNameChar = noteName[0];
    int alter_num = std::stoi(alter);
    if (noteNameChar == 'C') {
        midiNumber = 0;
    } else if (noteNameChar == 'D') {
        midiNumber = 2;
    } else if (noteNameChar == 'E') {
        midiNumber = 4;
    } else if (noteNameChar == 'F') {
        midiNumber = 5;
    } else if (noteNameChar == 'G') {
        midiNumber = 7;
    } else if (noteNameChar == 'A') {
        midiNumber = 9;
    } else if (noteNameChar == 'B') {
        midiNumber = 11;
    }
    midiNumber += alter_num;

    midiNumber += ((octave_num + 2) * 12);
    return midiNumber;
}

int main() {
    rapidxml::file<> xmlFile("C:\\Users\\khaus\\CLionProjects\\arc-piano-hand\\src\\code_timeline\\fall2023\\Algos-code\\hotcrossmasked.musicxml");
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<> *title = doc.first_node();
    // handlenode(title, "note");


    for(auto note : find_notes(title)) {
        std::cout << note->toString() << std::endl;
    }

    /*
    std::vector<Note *> vec = find_notes(title);
    for (int i = 0; i < vec.size(); i++) {
        Note *note = vec[i];
    }
     */
}
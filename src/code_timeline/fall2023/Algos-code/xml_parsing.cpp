#include "rapidxml_utils.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void print_notes(rapidxml::xml_node<> *node) {
    for (node = node->first_node(); node != NULL; node = node->next_sibling()) {
        if (node->type() == rapidxml::node_element) //check node type
        {
           std::cout << node->name() << ": " << node->value() << std::endl;
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

class Note {
    public:
        char step;
        int octave;
        int duration; //quarter note = 16, half note = 32, sixteenth = 1

        char getStep(int noteOrder) { //noteOrder = 1 means that it's the first note, 2 the second note, etc.
            for (int i )
        }
};

int getMidiNumber(std::string noteName, int octave, std::string accidental) {
    int midiNumber = 0;
    if (noteName[0] == 'C') {
        midiNumber = 0;
    } else if (noteName[0] == 'D') {
        midiNumber = 2;
    } else if (noteName[0] == 'E') {
        midiNumber = 4;
    } else if (noteName[0] == 'F') {
        midiNumber = 5;
    } else if (noteName[0] == 'G') {
        midiNumber = 7;
    } else if (noteName[0] == 'A') { // if noteName is A
        midiNumber = 9;
    } else if (noteName[0] == 'B') {
        midiNumber = 11;
    }
    if (accidental == "sharp") {
        midiNumber++;
    } else if (accidental == "flat") {
        midiNumber--;
    }

    midiNumber += ((octave + 2) * 12);
    return midiNumber;
}

int main() {
    rapidxml::file<> xmlFile("C:\\Users\\TPNml\\Documents\\GitHub\\arc-piano-hand\\src\\code_timeline\\fall2023\\Algos-code\\rapidxml_testing\\hotcrossmasked.musicxml");
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<> *title = doc.first_node();
    handlenode(title, "note");


}
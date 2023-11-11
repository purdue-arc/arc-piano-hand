#include "phSpace.h"

using namespace phSpace;

void xml_parsing::print_notes(rapidxml::xml_node<> *node) {
    for (node = node->first_node(); node != nullptr; node = node->next_sibling()) {
        if (node->type() == rapidxml::node_element) //check node type
        {std::string x = node->value();
           std::cout << node->name() << ": " << x << std::endl;
           print_notes(node);
        }
    }
}

// Allows you to send nodes for
void xml_parsing::handlenode(rapidxml::xml_node<> *node, std::string x) {
    for (node = node->first_node(); node != nullptr; node = node->next_sibling()) {
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
rapidxml::xml_node<> * xml_parsing::search_for_node(rapidxml::xml_node<> *node, const std::string& x) {
    if (node == nullptr) return nullptr;
    for (node = node->first_node(); node != nullptr; node = node->next_sibling()) {
        if (node->type() == rapidxml::node_element) //check node type
        {
            //std::cout << node << std::endl;
            if (node->name() == nullptr) {
                return nullptr;
            } else if (x == node->name()) {
                return node;
            }
            rapidxml::xml_node<> *output = search_for_node(node, x);
            if (output != nullptr) {
                return output;
            }
        }
    }
    return nullptr;
}

Note * xml_parsing::parse_note(rapidxml::xml_node<> *node, int prev_time) { // Node is the root of the tree where the note is
    // Parse the tree and find the tag with the step
    // Alter
    // Octave
    // And duration
    // Store each of these in a variable
    // You can use the search_for_node function above which searches for a given tag in the tree

    Note *parsedNote = nullptr;
    std::string rest = "rest";
    if (!(node->first_node()->name() != nullptr && rest == node->first_node()->name())) {
        rapidxml::xml_node<> *note_name_ptr = search_for_node(node, "step");
        std::string note_name = note_name_ptr ? note_name_ptr->value() : "";
        rapidxml::xml_node<> *octave_ptr = search_for_node(node, "octave");
        std::string octave = octave_ptr ? octave_ptr->value() : "";
        rapidxml::xml_node<> *alter_ptr = search_for_node(node, "alter");
        std::string alter = alter_ptr ? alter_ptr->value() : "0";
        rapidxml::xml_node<> *duration_ptr = search_for_node(node, "duration");
        std::string duration = duration_ptr ? duration_ptr->value() : "";

        // std::cout << note_name << " " << octave << " " << alter << " " << duration << std::endl;
        // Then call the Note constructor with these values and return the resulting Note*/
        parsedNote = new Note(note_name, octave, alter, duration, prev_time);
    }
    return parsedNote;
}

std::vector<Note *> xml_parsing::find_notes(rapidxml::xml_node<> *node) {
    if (node == nullptr) return std::vector<Note *>{};
    std::vector<Note *> notes{};
    std::string x("note");
    int prevTime = 0;
    for (node = node->first_node(); node != nullptr; node = node->next_sibling()) {
        if (node->type() == rapidxml::node_element) //check node type
        {

            if (x == node->name()) {
                //print_notes(node);
                //handlenode(node, "step");
                Note *note = parse_note(node, prevTime);
                if (note != nullptr) {
                    prevTime = note->time;
                    notes.push_back(note); //add to the end
                }
            } else {
                std::vector<Note *> output = find_notes(node);
                notes.insert(notes.end(), output.begin(), output.end());
            }
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

    midiNumber += ((octave_num + 1) * 12);
    return midiNumber;
}

int main_bad() {
    rapidxml::file<> xmlFile("C:\\Users\\TPNml\\Downloads\\Hot.musicxml");
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<> *title = doc.first_node();
    // handlenode(title, "note");

    //std::cout << search_for_node(title, "octave") << std::endl;

    std::vector<Note *> notes = xml_parsing::find_notes(title);

    for(auto note : notes) {
        std::cout << note->toString() << std::endl;
    }

    /*
    std::vector<Note *> vec = find_notes(title);
    for (int i = 0; i < vec.size(); i++) {
        Note *note = vec[i];
    }
     */
    return 0;
}
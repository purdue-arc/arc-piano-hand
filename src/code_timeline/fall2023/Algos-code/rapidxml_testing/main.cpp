#include "rapidxml_utils.hpp"
#include <iostream>
#include <sstream>

void handlenode(rapidxml::xml_node<> *node) {
    for (node = node->first_node(); node != NULL; node = node->next_sibling()) {

        if (node->type() == rapidxml::node_element) //check node type
        {
            std::cout << node->name() << ": " << node->value() << std::endl;
            handlenode(node);
        }
    }
}

int main() {
    rapidxml::file<> xmlFile("C:\\Users\\khaus\\CLionProjects\\test_3\\hotcrossmasked.musicxml");
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<> *title = doc.first_node();
    handlenode(title);


}
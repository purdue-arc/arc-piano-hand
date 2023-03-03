#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Hand::Hand(int size)
{
    rotation = 0;
    position = 0;
    for (auto i = 0; i < size; i++) {
        fingers[i] = Finger::Finger(i, NULL_NOTE);
    }
}

Hand::Hand(std::vector<Finger> fingers)
{
    rotation = 0;
    position = 0;
    this->fingers = fingers;
}

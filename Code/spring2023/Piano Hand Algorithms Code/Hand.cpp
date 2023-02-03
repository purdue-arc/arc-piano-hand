#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Hand::Hand(int size)
{
    rotation = 0;
    position = 0;
    for (auto i = 0; i < size; i++) {
        fingers[i] = Finger::Finger();
    }
}

Hand::Hand(Finger fingers[])
{
    rotation = 0;
    position = 0;
    for (auto i = 0; i < sizeof(fingers); i++) {
        this->fingers[i] = fingers[i];
    }
}

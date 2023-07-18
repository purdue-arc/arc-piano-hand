#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Hand::Hand(int size)
{
    this->size = size;
    this->rotation = 0;
    this->position = 0;
    fingers = (Finger **) malloc(sizeof(Finger *) * this->size);
}

void Hand::free() {
    FingerState::free();
}
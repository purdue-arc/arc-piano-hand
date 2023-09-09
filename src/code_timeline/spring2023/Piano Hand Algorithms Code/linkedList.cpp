#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

LinkedList::LinkedList() {
    this->prev = NULL;
    this->next = NULL;
}

LinkedList::LinkedList(Node n) {
    *this = LinkedList::LinkedList();
    this->n = n;
}
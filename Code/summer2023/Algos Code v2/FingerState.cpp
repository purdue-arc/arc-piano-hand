#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

FingerState::FingerState() {
	this->size = 0;
	this->capacity = 0;
	this->state = nullptr;
}

FingerState::FingerState(int capacity) {
	this->size = 0;
	this->capacity = 0;
	this->state = (Finger **) malloc(capacity * sizeof(Finger *));
}

void FingerState::free() {
	std::free(this->state);
}

Finger * FingerState::get(int idx) {
	if (idx < 0 || idx > size) {
		throw std::out_of_range("Index out of range FingerState");
		return nullptr;
	}
	return state[idx];
}

int FingerState::getSize() {
	return size;
}
int FingerState::getCapacity() {
	return capacity;
}
int FingerState::add(Finger *f)
{
	if (size == capacity) {
		throw std::exception("FingerState add() call made when full");
		return pianoHandNamespace::SIZE_ERROR;
	}
	state[size] = f;
	size++;
	return pianoHandNamespace::OK;
}

Finger ** FingerState::getFingers()
{
	return state;
}

Note FingerState::get_note(Finger *f)
{
	for (int i = 0; i < size; i++) {
		Finger *f2 = state[i];
		if (f2->getID() == f->getID()) {
			return f2->getNoteCurrentlyBeingPlayed();
		}
	}
	return NULL;
}

bool FingerState::exists(Finger *f)
{
	for (int i = 0; i < size; i++) {
		Finger *f2 = state[i];
		if ((f2->getID() == f->getID()) && (f2->getNoteCurrentlyBeingPlayed().equals(f->getNoteCurrentlyBeingPlayed()))) {
			return true;
		}
	}
	return false;
}
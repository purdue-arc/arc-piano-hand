#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

FingerState::FingerState() {

}

int FingerState::size()
{
	return 0;
}

int FingerState::add(Finger f)
{
	return 0;
}

std::vector<Finger> FingerState::getFingers()
{
	return std::vector<Finger>();
}

std::vector<Note> FingerState::getNotes()
{
	return std::vector<Note>();
}

Finger FingerState::get(Note n)
{
	return Finger();
}

Note FingerState::get(Finger f)
{
	return Note();
}

#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Finger::Finger() {

}

Note Finger::getNoteCurrentlyBeingPlayed()
{
	return Note();
}

bool Finger::isNoteBeingPlayed()
{
	return false;
}

void Finger::setNoteCurrentlyBeingPlayed(Note note)
{
}

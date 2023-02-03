#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Finger::Finger() {
	
}

Note Finger::getNoteCurrentlyBeingPlayed()
{
	return noteCurrentlyPlaying;
}
bool Finger::isNoteBeingPlayed()
{
	return (&noteCurrentlyPlaying == NULL);
}

void Finger::setNoteCurrentlyBeingPlayed(Note note)
{
	noteCurrentlyPlaying = note;
}

void Finger::removeNoteBeingPlayed() {
	noteCurrentlyPlaying = NULL;
}

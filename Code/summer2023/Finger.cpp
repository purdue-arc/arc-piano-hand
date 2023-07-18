#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Finger::Finger(int id)
{
	this->id = id;
	this->noteCurrentlyPlaying = NULL_NOTE;
}

Finger::Finger(int id, Note n)
{
	this->id = id;
	this->noteCurrentlyPlaying = n;
}

int Finger::getID()
{
	return this->id;
}

Note Finger::getNoteCurrentlyBeingPlayed()
{
	return noteCurrentlyPlaying;
}
bool Finger::isNoteBeingPlayed()
{
	return (noteCurrentlyPlaying.equals(NULL_NOTE));
}

void Finger::setNoteCurrentlyBeingPlayed(Note note)
{
	noteCurrentlyPlaying = note;
}

void Finger::removeNoteBeingPlayed()
{
	noteCurrentlyPlaying = NULL_NOTE;
}

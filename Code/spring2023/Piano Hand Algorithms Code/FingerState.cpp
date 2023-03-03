#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

FingerState::FingerState() {
	this->state = {};
}

int FingerState::size()
{
	return state.size();
}

int FingerState::add(Finger f)
{
	state.push_back(f);
}

std::vector<Finger> FingerState::getFingers()
{
	return state;
}

std::vector<Note> FingerState::getNotes()
{
	std::vector<Note> notes{};
	for (Finger f : state) {
		notes.push_back(f.getNoteCurrentlyBeingPlayed());
	}
	return notes;
}


std::vector<Finger> FingerState::get(Note n)
{
	std::vector<Finger> fingersPlayingNote{};
	for (Finger f : this->getFingers()) {
		if (f.getNoteCurrentlyBeingPlayed().equals(n)) {
			fingersPlayingNote.push_back(f);
		}
	}
	return fingersPlayingNote;
}

Note FingerState::get(Finger f)
{
	for (Finger f2 : this->getFingers()) {
		if (f2.getID() == f.getID()) {
			return f2.getNoteCurrentlyBeingPlayed();
		}
	}
	return NULL;
}

std::vector<Finger> FingerState::getRemainingFingers()
{
	std::vector<Finger> notPlaying{};
	for (Finger f : this->getFingers()) {
		if (f.getNoteCurrentlyBeingPlayed().equals(NULL_NOTE)) {
			notPlaying.push_back(f);
		}
	}
	return notPlaying;
}
		
std::vector<Note> FingerState::getRemainingNotes(std::vector<Note> notesToPlay)
{
	std::vector<Note> notPlaying{};
	for (Finger f : this->getFingers()) {
		Note n = f.getNoteCurrentlyBeingPlayed();
		for (Note x : notesToPlay) {
			auto loc = std::find(notesToPlay.begin(), notesToPlay.end(), x);
			int index = loc - notesToPlay.begin();
			if (loc != notesToPlay.end()) {
				notesToPlay.erase(loc);
				loc = std::find(notPlaying.begin(), notPlaying.end(), x);
				if (loc != notPlaying.end()) {
					notPlaying.erase(loc);
				}
			}
			else {
				notPlaying.push_back(notesToPlay.at(index));
			}
		}
		
	}
	return notPlaying;
}

int FingerState::uniquifyFingerwise() {
	// To implement
	// Removes duplicates of fingers for debugging
}

int FingerState::uniquifyNotewise() {
	// To implement
	// Removes duplicates of notes for debugging
}
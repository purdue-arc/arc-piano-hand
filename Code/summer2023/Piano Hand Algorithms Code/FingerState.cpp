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

static FingerState null_state() {
	FingerState fs = FingerState::FingerState();
	fs.add(Finger::Finger(-1000));
	return fs;
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

FingerState FingerState::make_copy() {
	FingerState fs = FingerState::FingerState();
	for (Finger f : this->getFingers()) {
		fs.add(f);
	}
	return fs;
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

Finger FingerState::get_finger(Finger f)
{
	for (Finger f2 : this->getFingers()) {
		if ((f2.getID() == f.getID()) && (f2.getNoteCurrentlyBeingPlayed().equals(f.getNoteCurrentlyBeingPlayed()))) {
			return f2;
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
	std::vector<int> ids{};
	int i = 0;
	for (Finger f : this->getFingers()) {
		auto loc = std::find(ids.begin(), ids.end(), f.getID());
		if (loc != ids.end()) {
			this->state.erase(std::remove(this->state.begin(), this->state.end(), f), this->state.end());
			i++;
		} else {
			ids.push_back(f.getID());
		}
	}
	return i;
}

int FingerState::uniquifyNotewise() {
	std::vector<Note> note_ids{};
	int i = 0;
	for (Finger f : this->getFingers()) {
		if (!f.getNoteCurrentlyBeingPlayed().equals(NULL_NOTE)) {
			auto loc = std::find(note_ids.begin(), note_ids.end(), f.getNoteCurrentlyBeingPlayed());
			if (loc != note_ids.end()) {
				this->state.erase(std::remove(this->state.begin(), this->state.end(), f), this->state.end());
				i++;
			} else {
				note_ids.push_back(f.getNoteCurrentlyBeingPlayed());
			}
		}
	}
	return i;
}
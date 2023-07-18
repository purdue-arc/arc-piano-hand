#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Note::Note(int midi_note_value) {
	this->midi_note_value = midi_note_value;
}
Note::Note(int midi_note_value, int velocity) {
	this->midi_note_value = midi_note_value;
	this->velocity = velocity;
}
int Note::get_midi_note_value() {
	return midi_note_value;
}
int Note::get_velocity() {
	return velocity;
}
bool Note::equals(Note n) {
	return (n.get_midi_note_value() == this->get_midi_note_value()) &&
		   (n.get_velocity() == this->get_velocity());
}


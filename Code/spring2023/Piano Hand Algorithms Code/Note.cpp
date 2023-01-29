#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

Note::Note(int midi_note_value) {
	this->midi_note_value = midi_note_value;
}
int Note::get_midi_note_value() {
	return midi_note_value;
}
#pragma once
class Note
{
private:
	int midi_note_value;
public:
	Note(int midi_note_value);
	int get_midi_note_value();
};


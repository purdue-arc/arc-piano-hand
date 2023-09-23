//
// Created by nambias on 9/22/2023.
//

#include <iostream>

using namespace std;

int main()
{
    cout << "Hello";
    return 0;
}

class Note {
    // Represents a musical note with MIDI number and time to play
    int midiNumber;
    int time;
    // ... Constructors and methods ...
};

class Finger {
protected:
    int state; // Current state of the finger
    int midi;
    Note currentNote; // Currently played note

public:
    void playNote(Note note);
    void releaseNote();
    void moveTo(int midi);
};

class Thumb : public Finger {
    // Additional behaviors specific to the thumb (inheritance + polymorphism)
};

class IndexFinger : public Finger {
};

class MiddleFinger : public Finger {
};

class RingFinger : public Finger {
};

class PinkyFinger : public Finger {
};

class Hand { // if we want code to be adaptable (2 feet, 3 thumbs, etc...) we can use vectors
    Finger* fingers[5]; // Array to hold the five fingers

public:
    void moveHandTo(int midi);
    void playNoteOnHand(Note note);
    void release(); // basically a freeing of all memory
};


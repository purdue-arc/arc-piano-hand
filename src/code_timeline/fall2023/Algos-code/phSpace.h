//
// Created by nambias on 9/22/2023.
//

#include <iostream>
#include <vector>

namespace phSpace {
    #define NORMAL_HAND 0
    #define EMPTY_HAND 1
    #define NULL_NOTE -1

    class Note {
        // Represents a musical note with MIDI number and time to play
        int midiNumber;
        int time;
        Note(int midiNumber, int time);
        // ... Constructors and methods ...
    };

    class Finger {
    protected:
        int id;
        bool state; // Current state of the finger
        Note *currentNote; // Currently played note

    public:
        explicit Finger(int id);
        bool isPlaying();
        Note * getNote();
        void playNote(Note *note);
        void releaseNote();
        void moveTo(Note * note);
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

    public:
        std::vector<Finger *> fingers;
        int num_fingers();
        int midi_position;
        Hand(int start_position, int hand_type);
        void moveHandTo(int midi);
        void playNoteOnHand(Note note);
        void release(); // basically a freeing of all memory
    };

    class initial_idea {
    public:
        static std::vector<int> minMvmtsForNotes(const std::vector<int>& notes);
    };

    class Viterbi {
    public:
        static std::vector<int> run_algo(int n_layers, int layer_size,
                                         double (*lookup)(int start_i, int start_j, int end_i, int end_j));
    };
}



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
    public:
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
        int getID();
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
        void release(); // basically a freeing of all memory
    };

    class initial_idea {
    public:
        static std::vector<int> minMvmtsForNotes(const std::vector<int>& notes);
    };

    class Viterbi {
    protected:
        int trellis_length;
        std::vector<std::vector<Hand *>> possible_fingerings;
    public:
        Viterbi(int trellis_length);
        void update_fingerings(std::vector<Hand *>);
        int layerSize(int);
        int hand_cost(int, int, int, int);
        std::vector<Hand *> run_algo();
    };
}


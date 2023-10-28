//
// Created by TPNml on 10/17/2023.
//

#include "phSpace.h"

using namespace phSpace;

int main() {
    Viterbi v = Viterbi(8);
    // Input/output

    std::vector<std::vector<Note *>> noteSets = input_output::readNotes();

    for (std::vector<Note *> notes: noteSets) {
        // Finger State Allocation
        std::vector<Hand *> hands = finger_state_alloc::allocate_finger_state(BAD_HAND, notes);

        v.update_fingerings(hands);

        // Call Viterbi object to process values
        std::vector<Hand *> hand_output = v.run_algo(false);

        // Output the result
        std::cout << "---------------------\nAfter the note(s) ";
        for (Note *n: notes) {
            std::cout << n->toString() << ", ";
        }
        std::cout << "the optimal sequence of fingerings is this order: " << std::endl;
        std::cout << Hand::getOutputFromViterbi(hand_output);
        std::cout << std::endl << std::endl;
    }
}
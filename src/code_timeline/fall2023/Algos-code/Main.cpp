//
// Created by TPNml on 10/17/2023.
//

#include "phSpace.h"
#include "finger_state_alloc.cpp"
using namespace phSpace;

int main() {
    Viterbi v = Viterbi(5);
    // Input/output

    std::vector<Note> notes;

    // Finger State Allocation
    std::vector<Hand> hands = allocate_finger_state(*new std::vector<Hand>, *new Hand(0, NORMAL_HAND), notes);
    v.update_fingerings(hands);

    // Call Viterbi object to process values
    std::vector<Hand *> hand_output = v.run_algo();

    // Output the result
    output_function();
}
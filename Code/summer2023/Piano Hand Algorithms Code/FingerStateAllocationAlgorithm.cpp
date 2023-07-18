#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

static int OPERATION_CODE = 0;
static int LEVELS_OF_RECURSION = 0;

const static std::vector<FingerState> NULL_FSV = { FingerState::null_state() };

Layer FingerStateAllocAlgo(FingerState *inputFingerState,
                           std::vector<Note> *notesToAllocate) {
    Layer l = Layer::Layer();
    std::vector<FingerState> states = FSAA(inputFingerState, notesToAllocate);
    for (FingerState fs : states) {
        fs.uniquifyFingerwise();
        fs.uniquifyNotewise();
        Node n = Node::Node(costFunctions::aggregate_cost(fs), fs);
        l.add(n);
    }
    return l;
}

/*
 * This method takes a vector and returns a vector with all the elements in the
 * original except the one passed in as an argument here.
 */
template<typename T>
std::vector<T> allExceptElem(std::vector<T> v, T item) {
    std::vector<T> v2;
    copy(v.begin(), v.end(), back_inserter(v2));
    v2.erase(std::remove(v2.begin(), v2.end(), item), v2.end());
    return v2;
}

/*
 * The original call of this algorithm takes a FingerState with unallocated fingers
 * as well as a vector of notes to allocate and returns a vector with all the possible
 * FingerState note-to-finger mappings for Viterbi.
 */
std::vector<FingerState> FSAA(FingerState *inputFingerState,
                              std::vector<Note> *notesToAllocate) {
    int level_rec = LEVELS_OF_RECURSION;
    int fsize = inputFingerState->getRemainingFingers().size(); // Save fsize/nsize to an integer to avoid
                                                                // calling over and over again
    int nsize = notesToAllocate->size();
    std::vector<FingerState> outStates;
    if (fsize < nsize) {
        OPERATION_CODE = SIZE_ERROR;
        return NULL_FSV;
    }
    // We wrote out all the cases to save operations
    else if ((fsize == 1) && (nsize == 1)) {
        Finger f = Finger::Finger((inputFingerState->getRemainingFingers())[0].getID(), (*notesToAllocate)[0]);
        inputFingerState->add(f);
        outStates.push_back(*inputFingerState);
    }
    else if (nsize == 1) {
        Note n = (*notesToAllocate)[0];
        for (Finger f : inputFingerState->getRemainingFingers()) {
            FingerState copy_state = inputFingerState->make_copy();
            copy_state.get_finger(f).setNoteCurrentlyBeingPlayed(n);
            outStates.push_back(copy_state);
        }
    }
    else {
        for (Finger f : inputFingerState->getRemainingFingers()) {
            for (Note n : *notesToAllocate) {
                FingerState copy_state = inputFingerState->make_copy();
                copy_state.get_finger(f).setNoteCurrentlyBeingPlayed(n);
                std::vector<Finger> fingers_left = allExceptElem(inputFingerState->getRemainingFingers(), f);
                std::vector<Note> notes_left = allExceptElem(*notesToAllocate, n);
                assert(fingers_left.size() > 0);
                assert(notes_left.size() > 0);
                std::vector<FingerState> recur_fs = FSAA(&copy_state, &notes_left);
                copy(recur_fs.begin(), recur_fs.end(), back_inserter(outStates));
            }
        }
    }
    return outStates;
}
// TODO: How to make this less wasteful?
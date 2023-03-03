#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

// Has no return or arguments right now to not throw errors during compilation until it's finished
int FingerStateAllocationAlgorithm(Layer layer, std::vector<FingerState> tempFingerState,
                                    std::vector<Finger> fingersToAllocate,
                                    std::vector<Note> notesToAllocate) {
    //if (notesToAllocate.size() == 0) {
    //    layer.add(Node::Node(tempFingerState));
    //    return OK;
    //}

    if (fingersToAllocate.size() < notesToAllocate.size()) {
        return SIZE_ERROR;
    }

    if ((fingersToAllocate.size() == 1) && (notesToAllocate.size() == 1)) {
        
    }

}
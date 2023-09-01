#include "pianoHandNamespace.h"
using namespace pianoHandNamespace;

/*
 * This method takes a vector and returns a vector with all the elements in the
 * original except the one passed in as an argument here.
 */
template <typename T>
std::vector<T> allExceptElem(std::vector<T> v, T item)
{
    std::vector<T> v2;
    copy(v.begin(), v.end(), back_inserter(v2));
    v2.erase(std::remove(v2.begin(), v2.end(), item), v2.end());
    return v2;
}

void FCStep(Layer *l,
            int numStates, int capacity, FingerState *fs_list,
            std::vector<int> notes_left, Note *notesToAllocate,
            std::vector<int> fingers_left, Finger **fingersToAllocate)
{
    FingerState *fs_list_new = nullptr;
    int curr_numStates = numStates;
    for (int note_idx : notes_left)
    {
        Note note = notesToAllocate[note_idx];
        for (int finger_idx : fingers_left)
        {
            Finger finger = *(fingersToAllocate[finger_idx]);
            if (fs_list == nullptr)
            {
                FingerState f = FingerState::FingerState(capacity);
                finger.setNoteCurrentlyBeingPlayed(note);
                f.add(&finger);
                fs_list_new = &f;
                curr_numStates = 1;
            }
            else
            {
                fs_list_new = new FingerState[numStates * fingers_left.size()];
                for (int i = 0; i < numStates; i++)
                {
                    FingerState f_old = fs_list[i];
                    FingerState f = FingerState::FingerState(capacity);
                    for (int j = 0; j < f_old.getSize(); j++)
                    {
                        f.add(f_old.get(j));
                    }
                    finger.setNoteCurrentlyBeingPlayed(note);
                    f.add(&finger);
                }
                curr_numStates = numStates * fingers_left.size();
            }
            if (notes_left.size() == 1)
            {
                for (int i = 0; i < numStates; i++)
                {
                    FingerState *fs_permanent = (FingerState *)malloc(sizeof(FingerState));
                    *fs_permanent = fs_list_new[i];
                    Node *node = (Node *)malloc(sizeof(Node));
                    *node = Node::Node(0.0, fs_permanent);
                    l->add(node);
                }
            }
            else if (fingers_left.size() == 1)
            {
                throw std::exception("Ran out of fingers");
            }
            else
            {
                std::vector<int> notes_left_new = allExceptElem(notes_left, note_idx);
                std::vector<int> fingers_left_new = allExceptElem(fingers_left, finger_idx);
                assert(fingers_left.size() > 0);
                assert(notes_left.size() > 0);
                FCStep(l, curr_numStates, capacity, fs_list_new, notes_left_new, notesToAllocate, fingers_left_new, fingersToAllocate);
            }
        }
    }
}


Layer *FingerStateAllocAlgo(Hand *hand,
                            int num_notes, Note *notesToAllocate)
{
    assert(hand != nullptr);
    assert(notesToAllocate != nullptr);
    assert(num_notes > 0);
    if (num_notes > hand->getSize())
    {
        throw std::exception("More notes than fingers");
        return nullptr;
    }
    Layer *l = (Layer *)malloc(sizeof(Layer));
    std::vector<int> notes_left = {};
    for (int i = 0; i < num_notes; i++)
    {
        notes_left.push_back(i);
    }
    std::vector<int> fingers_left = {};
    for (int i = 0; i < hand->getSize(); i++)
    {
        fingers_left.push_back(i);
    }
    FCStep(l, 0, hand->getCapacity(), nullptr, notes_left, notesToAllocate, fingers_left, hand->getFingers());
    return l;
}


#include "Finger.cpp"

class Hand {

private:
    const int fingerCount {};
    const Finger fingers[fingerCount];

public:

    Hand(int fingerCount, int* fingerPins) : fingerCount { fingerCount }
    {
        for (int i = 0; i < fingerCount; i++) {
            this->fingers[i] = Finger(fingerPins[i], 180, 0);
        }
    }

    void moveFinger(int fingerNum, int duration) {
        fingers[fingerNum].move(duration);

    }

};


#include <Servo.h>
#define FINGER_COUNT 4

// note, duration ovtave voice

class Finger {
private: 
    int angle_rest;
    int angle_down;
    int dt;
    int liftUpTime; // 
    bool isDown;
    Servo servo;

    void moveDown(float hold) {
        servo.write(angle_down);
        liftUpTime = millis() + hold * 1000; // converting seconds to milliseconds
        isDown = true;
    }
    
    void moveDown() {
      servo.write(angle_down);
    }

    void moveUp() {
        servo.write(angle_rest);
    }

public:
    Finger(int pin, int angleDown, int angleRest = 110) {
        angle_down = angleDown;
        angle_rest = angleRest;
        isDown = false;
        servo.attach(pin);
    }

    // this does not move the fingers simultaneously
    // does not take advantage of millis() but only delay()
    void move(bool concurrent, float hold = .4) {
        hold *= 1000;
        if (!concurrent) {
          moveDown();
          delay(hold);
          moveUp();
          delay(hold);
        } else {
          moveDown(hold);
        }
    }

    void check() {
      // i think something funky happens if you try to move it to its position so I keep track if it is in its rest position already
      if (isDown && millis() >= liftUpTime) {
        moveUp();
        isDown = false;
      }
      
    }


};

class Hand {
private:
    int fingerCount;
    unsigned long fingerTimes[FINGER_COUNT]; // keep track of the hold delays on the finger times
    Finger *fingers[FINGER_COUNT];

public:
    Hand(int numFingers, int* fingerPins) {
      fingerCount = numFingers;
      for (int i = 0; i < fingerCount; i++) {
          Finger fingers[i] = Finger(fingerPins[i], 180, 110); // Default values for angleDown and angleRest
      }
    }

    void moveFingerConcurrently(int fingerNum, float hold = .4) {
      hold *= 1000;
      fingers[fingerNum]->move(true, hold);
    }

    void moveFingerNonConcurrently(int fingerNum, float duration) {
      duration *= 1000;
      fingers[fingerNum]->move(false, duration);
    }

// function to check if it is time to move fingers up yet
    void checkFingers() {
      for (int finger; finger < fingerCount; finger++) {
        fingers[finger]->check();
      }
    }
};

int fingerPins[FINGER_COUNT] = {9, 10, 11, 6}; // Example pins, adjust as needed
Hand myHand(FINGER_COUNT, fingerPins);

void setup() {
    // Nothing needed here for this example  

}

void loop() {



}

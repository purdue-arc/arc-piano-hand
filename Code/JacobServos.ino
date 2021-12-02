#include <Servo.h>

Servo pinkyServo;
Servo ringServo;
Servo middleServo;
Servo pointerServo;
Servo thumbServo;
Servo wristServo;

int thumbAngle = 0;
int pointerAngle = 0;
int middleAngle = 0;
int ringAngle = 0;
int pinkyAngle = 0;

int wristAngleOffset = 0;
const int defaultWristAngle = 90;
const int pressKeyAngle = 30;

void setup() {
  pinkyServo.attach(3);
  ringServo.attach(5);
  middleServo.attach(6);
  pointerServo.attach(9);
  thumbServo.attach(10);
  wristServo.attach(11); 
    
  Serial.begin(9600);
  
  pinkyServo.write(0);
  ringServo.write(0);
  middleServo.write(0);
  pointerServo.write(0);
  thumbServo.write(0);
  wristServo.write(defaultWristAngle);
  delay(1000);
}

void loop() {
  playKey("C3");
  playKey("C#");
  playKey("D");
  playKey("D#");
  playKey("E");
  playKey("F");
  playKey("F#");
  playKey("G");
  playKey("G#");
  playKey("A");
  playKey("A#");
  playKey("B");
  playKey("C4");  	
}

// Plays the given key and goes back to default pos
void playKey(String key) {
  setAngles(key);
  moveServos();
  resetFingerJoints();
}

// Sets finger/wrist angle based on key pressed
// Note: must distinguish between C3 and C4
// Note: accidentals are always sharp
void setAngles(String key) {
  if (key.equals("C3")) {
    wristAngleOffset = 0;
    thumbAngle = pressKeyAngle;
    
  } else if (key.equals("C#")) {
    wristAngleOffset = 15;
    pointerAngle = pressKeyAngle;
    
  } else if (key.equals("D")) {
    wristAngleOffset = 7;
    pointerAngle = pressKeyAngle;
    
  } else if (key.equals("D#")) {
    wristAngleOffset = 0;
    pointerAngle = pressKeyAngle;
    
  } else if (key.equals("E")) {
    wristAngleOffset = 3;
    middleAngle = pressKeyAngle;
    
  } else if (key.equals("F")) {
    wristAngleOffset = 0;
    middleAngle = pressKeyAngle;
    
  } else if (key.equals("F#")) {
    wristAngleOffset = -5;
    middleAngle = pressKeyAngle;
    
  } else if (key.equals("G")) {
    wristAngleOffset = 0;
    ringAngle = pressKeyAngle;
    
  } else if (key.equals("G#")) {
    wristAngleOffset = -3;
    ringAngle = pressKeyAngle;
    
  } else if (key.equals("A")) {
    wristAngleOffset = 0;
    pinkyAngle = pressKeyAngle;
    
  } else if (key.equals("A#")) {
    wristAngleOffset = -5;
    pinkyAngle = pressKeyAngle;
    
  } else if (key.equals("B")) {
    wristAngleOffset = -8;
    pinkyAngle = pressKeyAngle;
    
  } else if (key.equals("C4")) {
    wristAngleOffset = -12;
    pinkyAngle = pressKeyAngle;
  }
  
}

// Gives time for the finger and wrist to move
void moveServos() {
  setFingerJoints();
  wristServo.write(defaultWristAngle + wristAngleOffset);
  delay(300);
}

// Gives time for the fingers to return to normal pos
void resetFingerJoints() {
  thumbAngle = 0;
  pointerAngle = 0;
  middleAngle = 0;
  ringAngle = 0;
  pinkyAngle = 0;
  setFingerJoints();
  delay(250); 
}

void setFingerJoints() {
  thumbServo.write(thumbAngle);
  pointerServo.write(pointerAngle);
  middleServo.write(middleAngle);
  ringServo.write(ringAngle);
  pinkyServo.write(pinkyAngle);
}

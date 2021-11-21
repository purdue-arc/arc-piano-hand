#include <Servo.h>

Servo pinkyServo;
Servo ringServo;
Servo middleServo;
Servo pointerServo;
Servo thumbServo;
Servo wristServo;

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

// Note: must distinguish between C3 and C4
// Note: accidentals must be sharp
void playKey(String key) {
  
  // Run through the keys and set finger/wrist pos
  if (key.equals("C3")) {
    wristAngleOffset = 0;
    thumbServo.write(pressKeyAngle);
    
  } else if (key.equals("C#")) {
    wristAngleOffset = 15;
    pointerServo.write(pressKeyAngle);
    
  } else if (key.equals("D")) {
    wristAngleOffset = 7;
    pointerServo.write(pressKeyAngle);
    
  } else if (key.equals("D#")) {
    wristAngleOffset = 0;
    pointerServo.write(pressKeyAngle);
    
  } else if (key.equals("E")) {
    wristAngleOffset = -3;
    middleServo.write(pressKeyAngle);
    
  } else if (key.equals("F")) {
    wristAngleOffset = 0;
    middleServo.write(pressKeyAngle);
    
  } else if (key.equals("F#")) {
    wristAngleOffset = -5;
    middleServo.write(pressKeyAngle);
    
  } else if (key.equals("G")) {
    wristAngleOffset = 0;
    ringServo.write(pressKeyAngle);
    
  } else if (key.equals("G#")) {
    wristAngleOffset = -5;
    ringServo.write(pressKeyAngle);
    
  } else if (key.equals("A")) {
    wristAngleOffset = 0;
    pinkyServo.write(pressKeyAngle);
    
  } else if (key.equals("A#")) {
    wristAngleOffset = -5;
    pinkyServo.write(pressKeyAngle);
    
  } else if (key.equals("B")) {
    wristAngleOffset = -8;
    pinkyServo.write(pressKeyAngle);
    
  } else if (key.equals("C4")) {
    wristAngleOffset = -12;
    pinkyServo.write(pressKeyAngle);
      	
  }
  
  // Time for the finger and wrist to move
  for (int i = 0; i < 30; i++) {
    wristServo.write(defaultWristAngle + wristAngleOffset);
  	delay(30);
  }
  
  // Time for the fingers to return to normal pos
  thumbServo.write(0);
  pointerServo.write(0);
  middleServo.write(0);
  ringServo.write(0);
  pinkyServo.write(0);
  delay(200);
}

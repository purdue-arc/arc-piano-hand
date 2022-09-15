#include <Servo.h>

#define SERV_CCW(SC) (90 + ((SC) / 3))
#define SERV_CW(SC) (90 - ((SC) / 3))
#define SERV_STILL 90

#define ANGLE_THRESH 5
#define CW_TEST 60
#define CCW_TEST 120
#define SERVO_DELAY 200

Servo ph_servo0;
Servo ph_servo1;

float x, x2, x3, x4, x5;
float maxFlex[5];
float minFlex[5];
int angle, angle2;
int prev_angle = 1000;  // some random high value
int prev_angle2 = 1000; //another random high value
int servo_set;
int servo_val(float analog_val);
void servo_pos(int angle, int prev_angle);

// NOTES TO do:

// Servo_Val needs to be changed, further discretised
// add a Callibration function
// Servo_control function to pass value from servo_val

void callibration(){
  // Wait 3 seconds!
  Serial.print("Press down on keyboard");
  delay(3000);
  //access array with finger readings
  float maxFlex[] = {analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3), analogRead(A4)};
  // Wait 3 seconds!
  delay(3000);
  Serial.print("Open hand");
  float minFlex[] = {analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3), analogRead(A4)};
  //create linear function to map flex to servo angle between 0 and 90
  
}



void setup()
{
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  ph_servo0.attach(9);
  ph_servo1.attach(8);
  Serial.begin(9600);
  callibration();
}

void loop()
{ 
  //ph_servo0.write(130);
  
  x = analogRead(A0);
  x2 = analogRead(A1);
  x3 = analogRead(A2);
  x4 = analogRead(A3);
  x5 = analogRead(A4);
  angle = servo_val(x);
  angle2 = servo_val(x2);

  // if (prev_angle != 1000) {
  // Serial.print("1: ");
  // Serial.print(angle);
  // Serial.print(", 2: ");
  // Serial.println(angle2);
  
  // Serial.print("1: ");
  // Serial.print(x);
  // Serial.print(", 2: ");
  // Serial.println(x2);
  //   servo_pos(angle, prev_angle);

  //   ph_servo0.write(servo_set);
  // }

  if (angle > prev_angle + 5) {
    ph_servo0.write(CCW_TEST);
  } else if (angle < prev_angle - 5) {
    ph_servo0.write(CW_TEST);
  } else {
    ph_servo0.write(SERV_STILL);
  }

  if (angle2 > prev_angle2 + 5) {
    ph_servo1.write(CCW_TEST);
  } else if (angle2 < prev_angle2 - 5) {
    ph_servo1.write(CW_TEST);
  } else {
    ph_servo1.write(SERV_STILL);
  }

  prev_angle = angle;
  prev_angle2 = angle2;
  delay(SERVO_DELAY);
  // delay(100); // to include a buffer between two different readings
  
}

int servo_val(float analog_val) {
  // calculates the angle from one of the methods discussed in #general
  float c_analogVal = ((analog_val - 159) / 352);
  int angle = (c_analogVal * 180);
  return angle;
}

void servo_pos(int angle, int prev_angle) {
  // anti-clockwise = down == angle < prev_angle
  
  if (angle > prev_angle) {
    ph_servo0.write(120);
  } else if (angle < prev_angle) {
    ph_servo0.write(60);
  } else {
    ph_servo0.write(SERV_STILL);
  }
  
}
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

float x, x2;
int angle, angle2;
int prev_angle = 1000;  // some random high value
int prev_angle2 = 1000;
int servo_set;

int servo_val(float analog_val);
void servo_pos(int angle, int prev_angle);

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  ph_servo0.attach(9);
  ph_servo1.attach(8);
  Serial.begin(9600);
}

void loop()
{ 
  //ph_servo0.write(130);
  
  x = analogRead(A0);
  x2 = analogRead(A1);
  angle = servo_val(x);
  angle2 = servo_val(x2);

  // if (prev_angle != 1000) {
  Serial.print("1: ");
  Serial.print(angle);
  Serial.print(", 2: ");
  Serial.println(angle2);

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
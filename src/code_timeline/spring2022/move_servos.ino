#include <servo.h>

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int pin0 = 0;
int pin1 = 1;
int pin2 = 2;
int pin3 = 3;
int pin4 = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  servo0.attach(pin0);
  servo0.attach(pin1);
  servo0.attach(pin2);
  servo0.attach(pin3);
  servo0.attach(pin4);

  servo0.write(90);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo0.write(180);
  servo1.write(180);
  servo2.write(180);
  servo3.write(180);
  servo4.write(180);

  delay(500);

  servo0.write(90);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);

  delay(500);
  
  servo0.write(0);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);

  delay(500);
  
  servo0.write(90);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);

  delay(500);
}

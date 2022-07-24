#include <Servo.h>

Servo servo;

int pin = 9;
int minimum = 0;
int maximum = 0;
int prev = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  servo.attach(pin);
  delay(2000);
  minimum = analogRead(A0);
  delay(2000);
  Serial.println("min read");
  maximum = analogRead(A0);
  Serial.println("max read");
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(A0);

  x = map(x, minimum, maximum, 0, 90);
  if (x > prev) {
    servo.write(0);
  } else {
    servo.write(180);
  }
  delay((0.175 * x) / 90);
  servo.write(90);
  prev = x;
}

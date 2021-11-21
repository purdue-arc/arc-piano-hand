#include <Servo.h>
// Create a servo object 
Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
Servo Servo6;
Servo servos[5] = {Servo1,Servo2,Servo3,Servo4,Servo5,Servo6};
void setup() { 
   // We need to attach the servo to the used pin number 
   	Servo1.attach(3); 
  	Servo2.attach(6); 
  	Servo3.attach(9); 
  	Servo4.attach(10); 
  	Servo5.attach(11); 
  	Servo6.attach(13); 
}
void loop(){ 
   // Make servo go to 0 degrees 
   //Servo1.write(0); 
  	moveFinger(1,90);
   	delay(1000); 
  	moveFinger(1,0);
   // Make servo go to 90 degrees 
   //Servo1.write(90); 
   delay(1000);
}
void moveFinger(int fingerNum, int degrees){
  servos[fingerNum].write(degrees);
}
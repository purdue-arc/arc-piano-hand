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
void stretchFingers(int note){
	//do calculation to get degree servo needs to move to
	//for now just setting degree to note
	int degree = note
	moveFinger(5,degree)
	pushWhiteKeys(note)
	pushBlackKeys(note)
}
#1-5
void pushBlackKeys(int note){
	if(note <=2)
	{
		moveFinger(0,90)
		delay(500)
		moveFinger(0,0)
	}
	else if(note <= 4){
		moveFinger(1,90)
		delay(500)
		moveFinger(1,0)
	}
	else if(note <= 5){
		moveFinger(3,90)
		delay(500)
		moveFinger(3,0)
	}
}
#A-G corresponds to 1-8
void pushWhiteKeys(int note){
	//not final numbers
	if(note <=3)
	{
		moveFinger(0,90)
		delay(500)
		moveFinger(0,0)
	}
	else if(note <= 6){
		moveFinger(1,90)
		delay(500)
		moveFinger(1,0)
	}
	else if(note <= 8){
		moveFinger(3,90)
		delay(500)
		moveFinger(3,0)
	}
}

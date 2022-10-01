float x, x2, x3, x4, x5;
float slopes[5];
float intercepts[5];
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
  Serial.print("Press down on keyboard\n");
  delay(3000);
  //access array with finger readings
  float maxFlex[5] = {analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3), analogRead(A4)};

  Serial.print("Finger Values: ");
  Serial.print(analogRead(A0));
  Serial.print("\n");
  Serial.print("Open hand\n");// Wait 3 seconds!
  delay(3000);
  Serial.print("Done!\n");
  float minFlex[5] = {analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3), analogRead(A4)};

  Serial.print("Finger Values: ");
  Serial.print(analogRead(A0));
  Serial.print("\n");
  //create linear function to map flex to servo angle between 0 and 90

  for (int i = 0; i < 5; i++)
  {
    slopes[i] = (90) / (maxFlex[i] - minFlex[i]);
    Serial.print("Slope of finger ");
    Serial.print(i +1);
    Serial.print(" is ");
    Serial.print(slopes[i]);
    Serial.print(".\n");
    intercepts[i] = slopes[i]* maxFlex[i] - 90;
  }
}



void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  Serial.begin(9600);
  callibration();
}

void loop()
{ 
  //ph_servo0.write(130);

  x = analogRead(A0);
  Serial.print("Raw Value: ");
  Serial.print(x);
  Serial.print("\nConverted Value: ");
  Serial.print(x * slopes[0] - intercepts[0]);
  Serial.print("\n");
  delay(3 00); // to include a buffer between two different readings

}

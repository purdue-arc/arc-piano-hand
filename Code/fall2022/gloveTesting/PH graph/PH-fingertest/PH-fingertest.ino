float x1, x2, x3, x4, x5;
float slopes[5];
float intercepts[5];
int angle, angle2;
int prev_angle = 1000;  // some random high value
int prev_angle2 = 1000; //another random high value
int servo_set;
byte pins[] = {A0, A1, A2, A3, A4};

int servo_val(float analog_val);
void servo_pos(int angle, int prev_angle);

void callibration() {
  Serial.print("Close hand!\n");
  float maxFlex[5];
  getAverageValues(maxFlex);
  // Access array with finger readings
  // Serial.print("Finger Values: ");
  // Serial.print(analogRead(A0));
  // Serial.print("\n");

  Serial.print("Open hand\n");// Wait 3 seconds!
  float minFlex[5];
  getAverageValues(minFlex);
  
  Serial.print("Done!\n");
  // access array with finger readings
  // Serial.print("Finger Values: ");
  // Serial.print(analogRead(A0));
  // Serial.print("\n");

  for (int i = 0; i < 5; i++) {
    slopes[i] = (90) / (maxFlex[i] - minFlex[i]);
    intercepts[i] = slopes[i]* maxFlex[i] - 90;
  }
}

// Read the analog value of each finger and take the average
void getAverageValues(float* flexArray) {
  // Wait 3 seconds
  delay(3000);
  //set all maxflex values to 0
  for (int i = 0; i < 5; i++) { flexArray[i] = 0; }
  
  // Loop for every time reading
  for (int i = 0; i < 5; i++) {
    // Loop over each finger
    for (int j = 0; j < 5; j++) {
      flexArray[j] += analogRead(pins[j]);
    }
    delay(500);
    Serial.print("Logging flex values: \n");
    Serial.print(i);
    Serial.print(" times completed\n");
  }
  for (int i = 0; i < 5; i++) {
      flexArray[i] = flexArray[i] / 5;
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

  /* Raw value will most likely never be used ;(
  Serial.print("Raw Value: ");
  Serial.print(x1);
  */
  //Serial.print("\nConverted Value: ");
  // Finger 1
  x1 = analogRead(A0);
  Serial.println(x1 * slopes[0] - intercepts[0]);
  // Finger 2
  x2 = analogRead(A1);
  Serial.println(x2 * slopes[1] - intercepts[1]);
  // Finger 3
  // x3 = analogRead(A2);
  // Serial.println(x3 * slopes[2] - intercepts[2]);
  // Finger 4
  // x4 = analogRead(A3);
  // Serial.println(x4 * slopes[3] - intercepts[3]);
  // Finger 5
  // x5 = analogRead(A4);
  // Serial.println(x5 * slopes[4] - intercepts[4]);
  delay(100); // to include a buffer between two different readings
}


int angle;
int prev_angle = 1000;  // some random high value
int servo_set;

int temp_num_fingers = 2;
const int NUM_FINGERS = 5;
float slopes[NUM_FINGERS];
float intercepts[NUM_FINGERS];
float fingerValues[NUM_FINGERS];
byte pins[] = {A0, A1, A2, A3, A4};

int servo_val(float analog_val);
void servo_pos(int angle, int prev_angle);

void setup()
{
  // Set up each finger
  for (int i = 0; i < NUM_FINGERS; i++) {
    pinMode(pins[i], INPUT);
  }
  Serial.begin(9600);
  run_callibration();
}

void run_callibration() {
  Serial.print("Close hand!\n");
  float maxFlex[NUM_FINGERS];
  getAverageValues(maxFlex);
  // Access array with finger readings
  // Serial.print("Finger Values: ");
  // Serial.print(analogRead(A0));
  // Serial.print("\n");

  Serial.print("Open hand\n");// Wait 3 seconds!
  float minFlex[NUM_FINGERS];
  getAverageValues(minFlex);
  
  Serial.print("Done!\n");
  // Access array with finger readings
  // Serial.print("Finger Values: ");
  // Serial.print(analogRead(A0));
  // Serial.print("\n");

  for (int i = 0; i < NUM_FINGERS; i++) {
    slopes[i] = 90 / (maxFlex[i] - minFlex[i]);
    intercepts[i] = slopes[i] * maxFlex[i] - 90;
  }
}

// Read the analog value of each finger and take the average
void getAverageValues(float* flexArray) {
  delay(3000);
  // Set all maxflex values to 0
  for (int i = 0; i < NUM_FINGERS; i++) { flexArray[i] = 0; }
  
  // Loop for every time reading
  int num_readings = 5;
  for (int i = 0; i < num_readings; i++) {
    // Loop over each finger add sum up the readings
    for (int j = 0; j < NUM_FINGERS; j++) {
      flexArray[j] += analogRead(pins[j]);
    }
    delay(500);
    Serial.print("Logging flex values: \n" + i);
    Serial.println(" times completed");
  }
  // Calculate the average of each finger
  for (int i = 0; i < NUM_FINGERS; i++) {
      flexArray[i] = flexArray[i] / num_readings;
  }
}

void loop()
{ 
  // Serial.print("\nConverted Value: ");
  for (int i = 0; i < temp_num_fingers; i++) {
    // Raw value will most likely never be used ;(
    // Serial.print("Raw Value: ");
    // Serial.print(x1);
    fingerValues[i] = analogRead(pins[i]);
    Serial.println(fingerValues[i] * slopes[i] - intercepts[i]);
  }
  delay(100); // to include a buffer between two different readings
}
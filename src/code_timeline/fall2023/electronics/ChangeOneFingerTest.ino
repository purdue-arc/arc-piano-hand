constexpr int fingerCount = 1;
const int fingerPotPins[1] = {A1};
const int fingerPins[fingerCount] = {1};
int currPotVal {0};
int currAngles[fingerCount]; 

int speedPin = 10;
int directionPinOne = 9;
int directionPinTwo = 8;
// 0 -255
int motSpeed= 150;

int motorPin = 3;

void moveFinger(int voltage, const int fingerPin);
int convertPotValToAngle(int potVal);
int getCurrAngle(int fingerPin);
int* getTargetAngles();
void positionOneFinger(int targetAngle, int currAngle, int fingerPin);
void positionAllFingers(int targetAngle[], int currAngles[], int fingerPins[]);


void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);
  pinMode(fingerPotPins[0], INPUT);
  pinMode(speedPin, OUTPUT);
  pinMode(directionPinOne, OUTPUT);
  pinMode(directionPinTwo, OUTPUT);
  Serial.begin(9600);
  delay(100);
}

void loop() {
  currAngles[0] = analogRead(fingerPotPins[0]);
  const int targetAngle = 600;
  positionOneFinger(targetAngle, currAngles[0], motorPin);
  delay(1000);
}

// will position fingers toward the target angles wanted
void positionAllFingers(int targetAngles[], int currAngles[], int fingerPins[])
{
  for (int i = 0; i < fingerCount; ++i)
    positionOneFinger(targetAngles[i], currAngles[i], fingerPins[i]);
}

void positionOneFinger(int targetAngle, int currAngle, int fingerPin)
{
  const int threshold {100};
  const int angle = currAngle - targetAngle;
  if (abs(angle) < threshold) 
    return;
  if (angle < 0)
    moveFinger(-angle, fingerPin, targetAngle); // moves finger in the negative direction
  else if (angle > 0) 
    moveFinger(angle, fingerPin, targetAngle); // moves finger in the positive direction
}

// will move the fingers by directly accessing motors
void moveFinger(int voltage, const int fingerPin, const int targetAngle)
{
  if (abs(voltage) > 255)
    voltage = 255;

  motSpeed = abs(voltage);
  const int threshold {100};
  if (voltage > 0) 
  {
    digitalWrite(directionPinOne, HIGH);
    digitalWrite(directionPinTwo, LOW);
  }
  else if (voltage < 0)
  {
    digitalWrite(directionPinOne, LOW);
    digitalWrite(directionPinTwo, HIGH);
  }
  analogWrite(speedPin, motSpeed);

  const int angle = getCurrAngle(fingerPin) - targetAngle;

  if (abs(angle) > threshold)
  {      
    if (angle < 0)
      moveFinger(angle / 2, fingerPin, targetAngle);
    else 
      moveFinger(-angle / 2, fingerPin, targetAngle);
  }
  else 
    moveFinger(0, fingerPin, targetAngle);
}


// Will convert the received potentiometer value into the angle the current fingle is positioned at
int convertPotValToAngle(int potVal)
{
  // convert the potval into angle below
  // the formula has not yet been implemented
  return potVal;
}

int getCurrAngle(int fingerPin)
{
  int potVal = analogRead(fingerPotPins[fingerPin]);
  return convertPotValToAngle(potVal);
}

int* getTargetAngles()
{
  // access angles from computer and return them
  int tmp[fingerCount] = {1};
  return tmp;
}
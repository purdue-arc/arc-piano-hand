const int fingerCount = 5; //number of fingers 
const float PI = 3.141592

const int fingerAnalogPins[fingerCount] = {"A1, A2 ,A3, A4, A5"};
const int fingerPins[fingerCount] = {1, 2, 3, 4, 5};

int currPotVal {0};
int currAngles[fingerCount] = {0, 0, 0, 0, 0}; 

//function headers

void moveFingers(int *, int *, int *);
void moveFinger(int, int, int);
int getCurrAngle(int);

void setup() {
  // put your setup code here, to run once:
  
  for (int i = 0; i < fingerCount; i++)
    pinMode(fingerPotPins[i], OUTPUT);
  Serial.begin(9600);
  
  delay(1000);
}


void loop() {
  // put your main code here, to run repeatedly:

  int i = 0
  while(Serial.avaliable() > 0) {
    vels[i] = (int) Serial.readString();
    force[i] = (int) Serial.readString();
    i++  
  }

  //reset i back to 0
  i = 0;
  moveFingers(fingerPins, vels, forces);
    
}

// will position finger towards the target angle wanted

void moveFingers(int *fingerPins, int *vels, int *forces)
{
  for (int i = 0; i < fingerCount; ++i)
  {
    positionOneFinger(fingerPin[i], vels[i], forces[i]);
  }, 
}

void moveFinger(int fingerPin, int velocity, int force)
{
  if (currAngle < targetAngle) {
    digitalWrite(dirPin, HIGH); 
    analogWrite(fingerPin, map(velocity, 0, 100, 0, 255));
  }
  else if (currAngle > targetAngle) {
    digitalWrite(dirPin, LOW);
    analogWrite(fingerPin, map(velocity, 0, 100, 0, 255));
  }

  int adjustedForce = map(force, 0, 100, 0, 255);
  analogWrite(fingerPin, adjustedForce);

  return;
}

int getCurrAngle(int fingerPin)
{
  //get the angle as an analog value
  int analogAngle = analogRead(fingerPins[fingerPin]);
  
  //get the angle in radians
  int angle = (float) analogAngle / 255 *
  
  return convertPotValToAngle(analogAngle);
}

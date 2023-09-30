const int fingerPotPins[1] = {"A1"};
const int fingerPins[5] = {1, 2, 3, 4, 5};
String getPotValsSignal = "p";
int currPotVal;
int[] currAngles; 

int currTime {0};
int positionFingerPrevTime {0};
int getPotValsPrevTime {0};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 1; ++i)
    pinMode(fingerPotPins[i], OUTPUT);
  Serial.begin(9600);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  currTime = millis();
  if (currTime - getPotValsPrevTime <= 10)
  {
    getPotValsPrevTime = currTime;
    if (Serial.available() > 0 && Serial.readString().equals(getPotValsSignal)) {
      currAngles = analogRead(fingerPotPins[0])
      Serial.println(currAngle);
    }
  }
  

  
  if (currTime - prevTime <= 20) 
  {
    prevTime = currTime;
    positionAllFingers(getTargetAngles(), currAngles, fingerPins);
  }


}

// will position finger towards the target angle wanted

positionAllFingers(int[] targetAngle, int[] currAngles, int[] fingerPins)
{
  for (int i = 0; i < fingerPins.length; ++i)
  {
    positionOneFinger(targetAngles[i], currAngles[i], fingerPins[i]);
  }
}

void positionOneFinger(int targetAngle, int currAngle, int fingerPin)
{
  const threshold {5};
  if (abs(currAngle - targetAngle) > threshold) 
  {
    moveFinger(0, fingerPin);
    return;
  }
  if (currAngle < targetAngle)
    moveFinger(100, fingerPin);
  else if (currAngle > targetAngl )  
    moveFinger(-100, fingerPin);
  return 
}

// will move the fingers by directly accessing motors
void moveFinger(int voltage, const int fingerPin)
{
  print("Move finger");
  return;
}

// Will convert the received potentiometer value into the angle the current fingle is positioned at
int convertPotValToAngle(int potVal)
{
  // convert the potval into angle below
  return 1;
}

int getCurrAngle(int fingerPin)
{
  int potVal = analogRead(fingerPotPins[fingerPin]);
  return convertPotValToAngle(potVal);
}

int[] getTargetAngles()
{
  // access angles from computer and return them
  return [0,1,2];
}
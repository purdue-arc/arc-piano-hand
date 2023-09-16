const int fingerPotPins[1] = {"A1"};
String getPotValsSignal = "p";

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 1; ++i)
    pinMode(fingerPotPins[i], OUTPUT);
  Serial.begin(9600);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0 && Serial.readString().equals(getPotValsSignal)) {
    Serial.println(analogRead(fingerPotPins[0]));


    int potVals[] = {0, 0, 0};
    for (int i = 0; i < 1; ++i) 
    {
        // String output = "Finger " + i;
        // String output2 = ": " + analogRead(fingerPotPins[i]);
        // Serial.println(output + output2);
        //Serial.println("Finger " + ": " + analogRead(fingerPotPins[i]);
    }

    
    

    // read pins
    // send pins
  }
}

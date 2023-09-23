const int fingerPotPins[1] = {A1};
String getPotValsSignal = "p";

void setup() {
  Serial.begin(9600);
  
    pinMode(A1, INPUT);
    delay(100);
}

void loop() 
{
  while (Serial.available() == 0) {}
  String inputVal = Serial.readString();
  inputVal.trim();
  
  if (inputVal == "p")
  {
    Serial.println(analogRead(fingerPotPins[0]));
  }
}




//void loop() {
//  Serial.println("Enter data:");
//  while (Serial.available() == 0) {}     //wait for data available
//  String teststr = Serial.readString();  //read until timeout
//  teststr.trim();                        // remove any \r \n whitespace at the end of the String
//  if (teststr == "red") {
//    Serial.println("A primary color");
//  } else {
//    Serial.println("Something else");
//  }
//}

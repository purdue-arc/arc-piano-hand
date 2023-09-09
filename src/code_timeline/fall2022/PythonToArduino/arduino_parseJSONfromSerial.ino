#include <ArduinoJson.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  String s = Serial.readString();
  StaticJsonDocument<256> jsonDoc;
  DeserializationError error = deserializeJson(jsonDoc, s);
  if (error) {
    Serial.println(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  } else {
      Serial.println("fingers: " + jsonDoc["fingers"].as<String>());
      Serial.println("move: " + jsonDoc["move"].as<String>());
   }
  delay(100);
}

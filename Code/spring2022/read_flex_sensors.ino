void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x0 = analogRead(A0);
  int x1 = analogRead(A0);
  int x2 = analogRead(A0);
  int x3 = analogRead(A0);
  int x4 = analogRead(A0);
  
  Serial.println(x0);
  Serial.println(x1);
  Serial.println(x2);
  Serial.println(x3);
  Serial.println(x4);

  delay(1000);
}

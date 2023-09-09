int enablef2 = 10;

int fig2f = 10;

int fig2r = 11;

int enablef1 = 9;

int fig1f = 10;

int fig1r = 11;

int enablef3 = 11;

int fig3f = 10;

int fig3r = 11;

int fingers[3] = {enablef1, enablef2, enablef3};
int directions[3][2] = {{fig1f, fig1r}, {fig2f, fig2r}, {fig3f, fig3r}};

void setup()
{

  Serial.begin(9600);

  pinMode(enablef2, OUTPUT);

  pinMode(fig2f, OUTPUT);

  pinMode(fig2r, OUTPUT);

  pinMode(enablef1, OUTPUT);

  pinMode(fig1f, OUTPUT);

  pinMode(fig1r, OUTPUT);

  pinMode(enablef3, OUTPUT);

  pinMode(fig3f, OUTPUT);

  pinMode(fig3r, OUTPUT);
//press(150,1,1000,1);
}

void loop() {
if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int values[4];
    int i = 0;
    char token = strtok((char)input.c_str(), ",");
    while (token != NULL) {
      values[i] = atoi(token);
      i++;
      token = strtok(NULL, ",");
    }
    if (i == 4) {
      int sped = values[0];
      int num = values[1];
      int timeheld = values[2];
      bool goReverse = values[3];
      press(sped, num, timeheld, goReverse);
      Serial.println("Command received and executed successfully.");
    } else {
      Serial.println("Invalid input.");
    }
    Serial.flush();
  }

}

void press(int sped, int num, int timeheld, bool goReverse)
{

 Serial.print("sped: ");
  Serial.println(sped);
  Serial.print("num: ");
  Serial.println(num);
  Serial.print("timeheld: ");
  Serial.println(timeheld);
  Serial.print("goReverse: ");
  Serial.println(goReverse);

  analogWrite(fingers[num], sped);
  digitalWrite(directions[num][goReverse], HIGH);
  digitalWrite(directions[num][!goReverse], LOW);
  delay(timeheld);
  analogWrite(fingers[num], sped);
  digitalWrite(directions[num][goReverse], LOW);
  digitalWrite(directions[num][!goReverse], HIGH);
  delay(timeheld);
  digitalWrite(directions[num][goReverse], LOW);
  digitalWrite(directions[num][!goReverse], LOW);


}

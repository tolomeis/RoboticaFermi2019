
int p1 = 8;
int p2 = 9;
int DIRPIN = 7;
int DIRPINB = 4;
int velPin = 6;
void setup() {
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(DIRPINB, OUTPUT);
  pinMode(DIRPIN, OUTPUT);
  
}

void loop() {

  if (digitalRead(p1) == HIGH) {
    digitalWrite(DIRPIN, 1);
    digitalWrite(DIRPINB, 0);
    analogWrite(velPin, 50);
    delay(5);
  } else {
    analogWrite(velPin, 0);
  }
  if (digitalRead(p2) == HIGH) {
    digitalWrite(DIRPIN, 0);
    digitalWrite(DIRPINB, 1);
    analogWrite(velPin, 50);
    delay(5);
  } else {
    analogWrite(velPin, 0);
  }
}

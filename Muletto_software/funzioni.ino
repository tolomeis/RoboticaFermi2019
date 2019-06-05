void prepara_Sensori() {
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]) {
    5, 4, 2
  }, SensorCount);
  delay(500);
  pinMode(buzzer, OUTPUT);
  tone(buzzer, 440, 1000);
  //calibrate for 5 seconds
  for (uint16_t i = 0; i < 200; i++) {
    qtr.calibrate();
  }
  tone(buzzer, 440, 500);
}

void linefollow() {
  //linefollow. Segui finchè non trova lo stop
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, HIGH); 
  const int sogliaStop = 750;
  do {
    position = qtr.readLineBlack(sensorValues);
    error = 1000 - position;
    vel = K * error;
    analogWrite(PWMA, (basevel - vel));
    analogWrite(PWMB, (basevel + vel));
  } while ((sensorValues[0] > sogliaStop) && (sensorValues[1] > sogliaStop) && (sensorValues[2] > sogliaStop));
  analogWrite(PWMA, 0); //mi fermo
  analogWrite(PWMB, 0);
}

void frena(){
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
}

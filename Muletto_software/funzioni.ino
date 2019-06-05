void prepara_Sensori(){
   // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]) { 5, 4, 2}, SensorCount);
  delay(500);
  pinMode(buzzer, OUTPUT);
  tone(buzzer, 440, 1000);
  //calibrate for 5 seconds
  for (uint16_t i = 0; i < 200; i++){
    qtr.calibrate();
  }
  tone(buzzer, 440, 500);
}

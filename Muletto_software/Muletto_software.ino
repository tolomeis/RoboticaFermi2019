#include <QTRSensors.h>

#define buzzer 7
#define PWMA  3
#define PWMB 11
#define DIRA 12 //A = DX
#define DIRB 13 //B = SX
#define SERVOPIN 6
#define P_VERDE A1
#define P_ROSSO A2
#define P_BLU A0

#define K 0.05

QTRSensors qtr;

const uint8_t SensorCount = 3;
uint16_t sensorValues[SensorCount];
int basevel = 80;
uint16_t position;
int error;
int vel;
void setup()
{
  prepara_Sensori();
  //set motors
  pinMode(DIRA, OUTPUT);  
  pinMode(DIRB, OUTPUT);
  digitalWrite(DIRA, LOW);  //imposto direzione
  digitalWrite(DIRB, HIGH);
  
  pinMode(P_VERDE, INPUT_PULLUP);
  
  while (digitalRead(P_VERDE)); //aspetta finchè non premo il pulsante verde


}

void loop() {
  //linefollow
  position = qtr.readLineBlack(sensorValues);
  error = 1000 - position;
  vel = K * error;
  analogWrite(PWMA, (basevel - vel));
  analogWrite(PWMB, (basevel + vel));


}

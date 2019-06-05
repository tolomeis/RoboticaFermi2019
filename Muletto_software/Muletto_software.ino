#include <COLORPAL.h>
#include <Servo.h>
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
enum {rosso, verde, blu, nessuno} colore, coloreDest;  //ci serve per scrivere nel programma i colori

QTRSensors qtr;
Servo carrello;

Colorpal colorp(10); //Sul Pin 10, credo

const uint8_t SensorCount = 3;
uint16_t sensorValues[SensorCount];
int basevel = 80;
uint16_t position;
int error;
int vel;
int nStop;
int c_rosso, c_verde, c_blu; // 3 variabili per le 3 componenti di colore

void setup()
{
  prepara_Sensori();
  //set motors
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  digitalWrite(DIRA, LOW);  //imposto direzione
  digitalWrite(DIRB, HIGH);
  //preparo i pulsanti
  pinMode(P_ROSSO, INPUT_PULLUP);
  pinMode(P_VERDE, INPUT_PULLUP);
  pinMode(P_BLU, INPUT_PULLUP);
  //preparo colorpal e servomotore
  carrello.attach(9);
  colorp.init();
  coloreDest = nessuno;
}

void loop() {
  //aspetto finché non viene premuto un pulsante di colore
  while (coloreDest = nessuno) {
    if (!digitalRead(P_ROSSO)) coloreDest = rosso;
    if (!digitalRead(P_VERDE)) coloreDest = verde;
    if (!digitalRead(P_BLU)) coloreDest = blu;
  }
  //Quando esco di qui coloreDest contiene il colore da trovare.
  //creo un ciclo che ri ripete finché non trovo il colore giusto
  colore = nessuno;
  nStop = 0;
  while (colore != coloreDest) {
    linefollow(); //seguo finché non trovo una tacca di stop, poi leggo il colore

    colorp.readRGB(c_rosso, c_verde, c_blu); //leggo le 3 componenti
    int cmax = max(c_rosso, c_verde); //prendo il max tra le 3 componenti di colore
    cmax = max(cmax, blu);
    if (cmax != 0) {       //controllo a cosa è uguale e assegno
      if (cmax == c_verde) colore = verde;
      if (cmax == c_rosso) colore = rosso;
      if (cmax == c_blu) colore = blu;
    }
    nStop++;
  }//quando esco di qui sarò sullo stop corrispondente al colore che devo prendereù

  //MANOVRA DI ROTAZIONE
  digitalWrite(DIRA, HIGH); //DX HIGH = INDIETRO
  digitalWrite(DIRB, HIGH); //SX avanti
  analogWrite(PWMA, 50);
  analogWrite(PWMB, 50);
  delay(1000);  //Si può fare con un delay o con la linea
  //while((position = qtr.readLineBlack(sensorValues)) != 1000);
  frena();

  digitalWrite(DIRA, LOW); //AVVICINAMENTO
  digitalWrite(DIRB, HIGH);
  analogWrite(PWMA, 50);
  analogWrite(PWMB, 50);
  delay(1000);
  frena();

  //sollevo
  carrello.write(80);
  delay(1000);
  carrello.write(90);

  //vado indietro
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
  analogWrite(PWMA, 50);
  analogWrite(PWMB, 50);
  delay(1000);
  frena();

  //GIRO DI ALTRI 90° per tornare sulla linea
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, HIGH);
  analogWrite(PWMA, 50);
  analogWrite(PWMB, 50);
  //delay(1000);
  while ((position = qtr.readLineBlack(sensorValues)) != 1000);
  frena();

  while (nStop) { //torno indietro oltrepassando un numero di linee uguale a quello che ho contato
    linefollow();
    nStop--;
  }
  frena();
  //abbassa carrello
  carrello.write(100);
  delay(1000);
  carrello.write(90);

}

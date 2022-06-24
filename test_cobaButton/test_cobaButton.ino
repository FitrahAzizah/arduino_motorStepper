#include <Wire.h>
#include <Math.h>

#define dirPin1 2
#define stepPin1 3
#define dirPin2 4
#define stepPin2 5
#define LS1 7 //LimitSwitch 1
#define LS2 50
#define PB1 47 //PushButton 1 (Merah)
#define PB2 49
#define PB3 51
#define PB4 53 //PushButton 4 (hijau)
#define degSens 9
#define stepsPerRevolution 800 // based on SW1-SW3 settings on motor driver's module

const float cmConv = 1.25;
const int degConv = 2;
boolean dir1, dir2;
int deg, dist, spd;
int statePB1 = 0;
int statePB2 = 0;
int statePB3 = 0;
int statePB4 = 0;


void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  pinMode(PB1, INPUT);
  pinMode(PB2, INPUT);
  pinMode(PB3, INPUT);
  pinMode(PB4, INPUT);
  pinMode(degSens, INPUT);

  digitalWrite(LS1, HIGH);
  digitalWrite(LS2, HIGH);
  digitalWrite(PB1, HIGH);

  Serial.begin(9600);
  Wire.begin();
}

void fwd(int spd, int cm) {
  digitalWrite(dirPin1, HIGH); // putar searah jarum jam
  for (unsigned long i = 0; i < stepsPerRevolution * cm * cmConv; i++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(spd); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(spd); // ganti delay untuk mempercepat motor

    boolean sens = digitalRead(LS2);
    if (sens == false) break;
  }
}

void rwd(int spd, int cm) {
  digitalWrite(dirPin1, LOW); // putar searah jarum jam
  for (unsigned long i = 0; i < stepsPerRevolution * cm * cmConv; i++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(spd); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(spd); // ganti delay untuk mempercepat motor

    boolean sens = digitalRead(LS1);
    if (sens == false) break;
  }

}

void cw(int spd, int deg) {
  int stepDeg = deg / 0.9 * degConv;
  digitalWrite(dirPin2, HIGH); // putar searah jarum jam
  for (unsigned long i = 0; i < stepDeg; i++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(spd); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(spd); // ganti delay untuk mempercepat motor
  }
}

void ccw(int spd, int deg) {
  int stepDeg = round(deg / 0.9 * degConv);
  digitalWrite(dirPin2, LOW); // putar searah jarum jam
  for (unsigned long i = 0; i < stepDeg; i++) {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(spd); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(spd); // ganti delay untuk mempercepat motor
  }
}

void loop() {
  statePB1 = digitalRead(PB1);
  if (statePB1 == HIGH){
    fwd(500, 5);
  }
  else fwd(500, 0);
  
  statePB2 = digitalRead(PB2);
  if (statePB2 == HIGH){
    rwd(500, 5);
  }
  else rwd(500, 0);
  
  statePB3 = digitalRead(PB3);
  if (statePB3 == HIGH){
    cw(500, 9);
  }
  else cw(500, 0);

  statePB4 = digitalRead(PB4);
  if (statePB4 == HIGH){
    ccw(500, 9);
  }
  else ccw(500, 0);
}

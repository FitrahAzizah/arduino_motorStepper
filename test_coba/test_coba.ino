#include <Wire.h>
#include <VL53L0X.h>
#include <Math.h>

#define dirPin1 2
#define stepPin1 3
#define dirPin2 4
#define stepPin2 5
#define LS1 7
#define LS2 50
#define degSens 9
#define stepsPerRevolution 800 // based on SW1-SW3 settings on motor driver's module

VL53L0X sensor;

const float cmConv = 1.25;
const int degConv = 2;
int mtSpd = 1000; //in milli second to control motor stepper speed
boolean dir1, dir2;
int deg, dist, spd;

int readDist();
float WeightedAverageFilter(float incomingValue, float previousValue);


void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  pinMode(degSens, INPUT);

  digitalWrite(LS1, HIGH);
  digitalWrite(LS2, HIGH);

  Serial.begin(9600);
  Serial.println("This device is ready to rock!");

  Wire.begin();

  sensor.init();
  sensor.setTimeout(500); // Set sensor timeout in milliseconds (0 = no timeout)
  sensor.startContinuous(); // Sensing interval

  if ((LS1 != false) || (degSens != false)) {
    goHome(100);
  }

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

void goHome(int spd) {
  boolean sens1, sens2;

  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, LOW);
  while (1) {
    while (1) {
      sens1 = digitalRead(LS1);
      if (sens1 == false) break;
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(spd); // ganti delay untuk mempercepat motor
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(spd); // ganti delay untuk mempercepat motor
    }

    while (1) {
      sens2 = digitalRead(degSens);
      if (sens2 == false) break;
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(spd); // ganti delay untuk mempercepat motor
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(spd); // ganti delay untuk mempercepat motor
    }

    Serial.print(sens1);
    Serial.println(sens2);
    if ((sens1 == false) && (sens2 == false)) break;

  }
}

void getdata() {
  String buf = Serial.readStringUntil('\n');

  int ind1 = buf.indexOf(',');  //finds location of first ,
  String Sdir1 = buf.substring(0, ind1);   //captures first data String
  int ind2 = buf.indexOf(',', ind1 + 1 ); //finds location of second ,
  String Sdir2 = buf.substring(ind1 + 1, ind2 + 1); //captures second data String
  int ind3 = buf.indexOf(',', ind2 + 1 ); //finds location of third,
  String Sdist = buf.substring(ind2 + 1, ind3 + 1); //capture third data String
  int ind4 = buf.indexOf(',', ind3 + 1 );
  String Sdeg = buf.substring(ind3 + 1, ind4 + 1); //captures remain part of data after last ,
  int ind5 = buf.indexOf(',', ind4 + 1);
  String Sspd = buf.substring(ind4 + 1);

  dir1 = Sdir1.toInt();
  dir2 = Sdir2.toInt();
  dist = Sdist.toInt();
  deg = Sdeg.toInt();
  spd = Sspd.toInt();

  Serial.print("FWD/RWD : ");
  Serial.println(dir1);
  Serial.print("CW/CCW : ");
  Serial.println(dir2);
  Serial.print("distance : ");
  Serial.println(dist);
  Serial.print("angle : ");
  Serial.println(deg);
  Serial.print("speed : ");
  Serial.println(spd);

}

int readDist() {
//  unsigned int reading;
//  
//  for (char i = 0; i < 10; i++) {
    int bReading = sensor.readRangeContinuousMillimeters();
//    reading += bReading;
//  }
//  reading = reading/10;
  return bReading;
}


void loop() {

  if (Serial.available()) {
    getdata();
    if (dir1 == true) fwd(spd, dist);
    else rwd(spd, dist);
    if (dir2 == true) cw(spd, deg);
    else ccw(spd, deg);

  }

  //int Distance = readDist();
  //Serial.print("Now Distance : ");
  //Serial.println(Distance);

}

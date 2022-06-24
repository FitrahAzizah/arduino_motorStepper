#include <AccelStepper.h> 
#define dirPin 2 // pin yang terhubung ke DIR+ motor driver
#define stepPin 3 // pin yang terhubung ke PUL+ motor driver
AccelStepper stepper = AccelStepper(1, stepPin, dirPin);
int rot=50;
void setup() {
  stepper.setMaxSpeed(1000); // atur kecepatan, dapat docoba dirubah untuk latihan
  stepper.setAcceleration(500); // nilai akselerasi / percepatan, dapat docoba dirubah untuk latihan
}
void loop() {
  if(rot>0){
    stepper.setCurrentPosition(0);
    rot--;
  }
  stepper.moveTo(800); // beri target 360*
  stepper.runToPosition(); //jalankan 
  //delay(1000); // jeda 1 detik
  //stepper.moveTo(0); // kembalikan ke posisi semula
  //stepper.runToPosition(); // jalankan
  //delay(1000); // jeda 2 detik
}

#define dirPin 4 
#define stepPin 5
#define fc33 9
#define stepsPerRevolution 800 // sesuaikan dengan settingan SW1-SW3 pada modul motor driver

boolean sens;
int cntRot;

void setup() {

  cntRot = 0;
  // put your setup code here, to run once:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(fc33, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  sens = digitalRead(fc33);
  Serial.println(sens);
   if (sens == HIGH){
    digitalWrite(LED_BUILTIN, HIGH);
   } else digitalWrite(LED_BUILTIN, LOW);
}

void startCW_aDegree(){
  cntRot++;
  digitalWrite(dirPin, HIGH); // putar searah jarum jam
   for (double i = 0; i < 2; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000); // ganti delay untuk mempercepat motor
  }
  Serial.print("count : ");
  Serial.println(cntRot);
}

void startCCW_aDegree(){
  Serial.print(" CW start : ");
  Serial.println(millis());
  digitalWrite(dirPin, LOW); // putar searah jarum jam
   for (double i = 0; i < 2; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000); // ganti delay untuk mempercepat motor
  }
  Serial.print("stop : ");
  Serial.println(millis());
}

void startCW_Full(){
  Serial.print(" CW start : ");
  Serial.println(millis());
  digitalWrite(dirPin, HIGH); // putar searah jarum jam
   for (double i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000); // ganti delay untuk mempercepat motor
  }
  Serial.print("stop : ");
  Serial.println(millis());
}

void startCCW_Full(){
  digitalWrite(dirPin, LOW); // putar searah jarum jam
   for (double i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000); // ganti delay untuk mempercepat motor
  }
  Serial.println(millis());
}

void loop() {
  // put your main code here, to run repeatedly:
while (Serial.available() > 0) {

  char buf = Serial.read();  // read the incoming byte:
  if (buf == '0'){
    startCW_aDegree();
  } else if(buf == '1'){
    startCCW_aDegree();
  } else if(buf == '2'){
    startCW_Full();
  } else if(buf == '3'){
    startCCW_Full();
  } else if(buf == '4'){
    cntRot = 0;
    for(int i=0;i<400;i++){
      startCW_aDegree();
      //delay(300);
    }
  }
}
 sens = digitalRead(fc33);
 if (sens == HIGH){
  digitalWrite(LED_BUILTIN, HIGH);
 } else digitalWrite(LED_BUILTIN, LOW);
}

#define dirPin 2
#define stepPin 3
#define fc33 9
#define ls1 7
#define ls2 50
#define stepsPerRevolution 800 // sesuaikan dengan settingan SW1-SW3 pada modul motor driver

//boolean sens, sens_ls1, sens_ls2;
char buf;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(fc33, INPUT);
  pinMode(ls1, INPUT);
  pinMode(ls2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(ls1, HIGH);
  digitalWrite(ls2, HIGH);

  Serial.begin(9600);

//  sens_ls1 = digitalRead(sens_ls1);
//  Serial.println(sens_ls1);
//  if (sens_ls = HIGH){
//    digitalWrite(LED_BUILTIN, HIGH);
//  }
//  else digitalWrite(LED_BUILTIN, LOW);

//  sens = digitalRead(fc33);
//  Serial.println(sens);
//  if (sens == HIGH) {
//    digitalWrite(LED_BUILTIN, HIGH);
//  } else digitalWrite(LED_BUILTIN, LOW);

}

void startFW() {
  Serial.print(" forward start : ");
  Serial.println(millis());
  digitalWrite(dirPin, HIGH); // putar searah jarum jam
  for (double i = 0; i < stepsPerRevolution * 6.25; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500); // ganti delay untuk mempercepat motor

    boolean sens = digitalRead(ls2);
    if (sens == false) break;
  }
  Serial.print("stop : ");
  Serial.println(millis());
}

void startRW() {
  Serial.print("reverse start : ");
  Serial.println(millis());
  digitalWrite(dirPin, LOW); // putar searah jarum jam
  for (double i = 0; i < stepsPerRevolution * 6.25; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000); // ganti delay untuk mempercepat motor

    boolean sens = digitalRead(ls1);
    if (sens == false) break;
  }
  Serial.print("stop : ");
  Serial.println(millis());
}

void goHome() {
  boolean sens;
  digitalWrite(dirPin, LOW); // putar searah jarum jam
  while (1) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500); // ganti delay untuk mempercepat motor
    sens = digitalRead(ls1);
    Serial.println(sens);
    if(sens == false) break;
  }
}

void loop() {
  if (Serial.available() > 0) {

    buf = Serial.read();  // read the incoming byte:
    if (buf == '1') {
      startFW();
    } else if (buf == '0') {
      startRW();
    } else if (buf == '2') {
      goHome();
    }
  }
  
//  sens = digitalRead(fc33);
//  //Serial.println(sens);
//  if (sens == HIGH) {
//    digitalWrite(LED_BUILTIN, LOW);
//  } else digitalWrite(LED_BUILTIN, HIGH);

//  sens_ls1 = digitalRead(sens_ls1);
//  Serial.println(sens_ls1);
//  if (sens_ls = HIGH){
//    digitalWrite(LED_BUILTIN, HIGH);
//  }
//  else digitalWrite(LED_BUILTIN, LOW);
}

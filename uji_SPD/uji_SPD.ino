#define dirPin1 2 
#define stepPin1 3
#define dirPin2 4 
#define stepPin2 5

#define stepsPerRevolution 800 // sesuaikan dengan settingan SW1-SW3 pada modul motor driver
void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);

  Serial.begin(9600);

  }

void rwd(){
   digitalWrite(dirPin1, LOW); // putar berlawanan jarum jam
   for (int i = 0; i < 40; i++) {
     digitalWrite(stepPin1, HIGH);
     delayMicroseconds(500); // ganti delay untuk mempercepat motor
     digitalWrite(stepPin1, LOW);
     delayMicroseconds(500); // ganti delay untuk mempercepat motor
   }
  
}

void fwd(){
  digitalWrite(dirPin1, HIGH); // putar berlawanan jarum jam
  for (int i = 0; i < 40; i++) {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500); // ganti delay untuk mempercepat motor
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500); // ganti delay untuk mempercepat motor
  }
  
}

void right(){
   digitalWrite(dirPin2, HIGH); // putar berlawanan jarum jam
   for (int i = 0; i < 50; i++) {
     digitalWrite(stepPin2, HIGH);
     delayMicroseconds(500); // ganti delay untuk mempercepat motor
     digitalWrite(stepPin2, LOW);
     delayMicroseconds(500); // ganti delay untuk mempercepat motor
   }
  
}

void left(){
   digitalWrite(dirPin2, LOW); // putar berlawanan jarum jam
   for (int i = 0; i < 50; i++) {
     digitalWrite(stepPin2, HIGH);
     delayMicroseconds(500); // ganti delay untuk mempercepat motor
     digitalWrite(stepPin2, LOW);
     delayMicroseconds(500); // ganti delay untuk mempercepat motor
   }
  
}

void loop() {
 while(Serial.available()){
  char c = Serial.read();
  if (c == 'f' || c == 'F'){
    fwd();
    Serial.println(c);
  } else if(c == 'b' || c == 'B'){
    rwd();
    Serial.println(c);
  } else if(c == 'r' || c == 'R'){
    right();
    Serial.println(c);
  } else if(c == 'l' || c == 'L'){
    left();
    Serial.println(c);
  }
 }
}

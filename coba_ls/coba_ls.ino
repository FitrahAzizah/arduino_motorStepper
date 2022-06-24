//#define ls1 7
#define ls2 50

boolean sens_ls1, sens_ls2;

void setup() {
  //pinMode(ls1, INPUT);
  pinMode(ls2, INPUT);
  digitalWrite(ls2, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {
//  sens_ls1 = digitalRead(ls1);
//  Serial.println(sens_ls1);
//  if (sens_ls1 = HIGH){
//    digitalWrite(LED_BUILTIN, HIGH);
//  }
//  else{
//    digitalWrite(LED_BUILTIN, LOW);
//  }

  sens_ls2 = digitalRead(ls2);
  Serial.println(sens_ls2);
  if (sens_ls2 == HIGH){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(1000);
}

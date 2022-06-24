int signPin = 5;
int signCount, tick;

void setup() {

  //init signal pin
    pinMode(signPin, INPUT);
    digitalWrite(signPin, LOW);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

  //setup timer2
    //ctc mode
    TCCR2A = (1 << WGM21);
    //prescaler 1024
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
    //8 ms, 16 MHz, prescaler 1024
    OCR2A = 155;//124 155 10ms
    //compare match
    TIMSK2 = (1 << OCIE2A);
    TCNT2 = 0;
  
  // put your setup code here, to run once:
  //setup counter 1, count on rising edge
    TCCR1B = (1 << CS12) | (1 << CS11) | (1 << CS10);
    TCNT1 = 0;

    Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(2);
}

ISR (TIMER2_COMPA_vect) // timer2 overflow interrupt
{
    //if (isReady) {
      //tick++;
      //if (tick >= 13) {
        //every 125*8 ms = 1000 ms
        //tick = 0;
        //cntReaded = 1;
        signCount = TCNT1;
        TCNT1 = 0;
        Serial.println(signCount);
      //}
    //}
}

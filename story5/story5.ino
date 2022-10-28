int RF = 7;
int RB = 8;
int RO = 9;
int LO = 10;
int LF = 11;
int LB = 12;

void forward() {
  digitalWrite(RF, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LF, HIGH);
}

void backward() {
  digitalWrite(RB, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LB, HIGH);
}
void Stop() {
  digitalWrite(RF, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LF, LOW);
  digitalWrite(RB, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LB, LOW);
}

void S_left() {
  digitalWrite(RF, HIGH);   // turn the LED on (HIGH is the voltage level)
  
}

void S_right() {
  digitalWrite(LF, HIGH);   // turn the LED on (HIGH is the voltage level)
  
}


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RF, OUTPUT);    //rightmotor fowrards
  pinMode(RB, OUTPUT);    //rightmotor backwards
  pinMode(RO, OUTPUT);
  pinMode(LO, OUTPUT);
  pinMode(LF, OUTPUT);   //leftmotor forwards
  pinMode(LB, OUTPUT);   //leftmotor backwards
  
  
}

// the loop function runs over and over again forever
void loop() {
  analogWrite(RO, 255);    // turn the LED off by making the voltage LOW
  analogWrite(LO, 255);
  
  
  forward();
  delay(1000);
  analogWrite(RO, 100);
  delay(1000);
  analogWrite(RO, 255);    // turn the LED off by making the voltage LOW
  analogWrite(LO, 100);
  delay(1000);
}

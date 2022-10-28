int RF = 7;
int RB = 8;
int RO = 9;
int LO = 10;
int LF = 11;
int LB = 12;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RF, OUTPUT);    //rightmotor fowrards
  pinMode(RB, OUTPUT);    //rightmotor backwards
  pinMode(RO, OUTPUT);
  pinMode(LO, OUTPUT);
  pinMode(LF, OUTPUT);   //leftmotor forwards
  pinMode(LB, OUTPUT);   //leftmotor backwards

  digitalWrite(RO, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(LO, HIGH);
  
  
}

// the loop function runs over and over again forever
void loop() {
  delay(1000);
  digitalWrite(RF, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(11, HIGH);
  delay(1000);
  digitalWrite(RF, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LF, LOW);// wait for a second
 delay(1000);
  digitalWrite(RB, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(LB, HIGH);
  delay(1000);  
  digitalWrite(RB, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LB, LOW);
  // wait for a second
}

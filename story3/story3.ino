

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(7, OUTPUT);    //rightmotor fowrards
  pinMode(8, OUTPUT);    //rightmotor backwards
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);   //leftmotor forwards
  pinMode(12, OUTPUT);   //leftmotor backwards

  digitalWrite(9, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(10, HIGH);
  
  
}

// the loop function runs over and over again forever
void loop() {
  delay(1000);
  digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(11, HIGH);
  delay(10000);
  digitalWrite(7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(11, LOW);// wait for a second
 delay(1000);
  digitalWrite(8, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(12, HIGH);
  delay(1000);  
  digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(12, LOW);
  // wait for a second
}

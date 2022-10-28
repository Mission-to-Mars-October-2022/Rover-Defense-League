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

void LeftMotorISR() {
  leftcounter++;
}

void RightMotorISR() {
  rightcounter++;
}

void Turnleft(int r_time) {
  digitalWrite(RF, HIGH);
  delay(r_time);
  Stop();
}

void Turnright(int r_time) {
  digitalWrite(LF, HIGH);
  delay(r_time);
  Stop();
}

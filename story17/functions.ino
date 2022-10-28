void forward() {
  digitalWrite(RB, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LB, LOW);
  digitalWrite(RF, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LF, HIGH);
}

void backward() {
  digitalWrite(RF, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LF, LOW);
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

void Turnleftbackward(int r_time) {
  digitalWrite(RB, HIGH);
  delay(r_time);
  Stop();
}

void Turnrightbackward(int r_time) {
  digitalWrite(LB, HIGH);
  delay(r_time);
  Stop();
}

void Rotateleft(int r_time) {
  digitalWrite(RF, HIGH);
  digitalWrite(LB, HIGH);
  delay(r_time);
  Stop();
}

void Rotateright(int r_time) {
  digitalWrite(LF, HIGH);
  digitalWrite(RB, HIGH);
  if (r_time > 0) {
    delay(r_time);
    Stop();
  }
}

int get_ldr_reading(int sensor_pin) {
  int sensor_reading = 0;
  sensor_reading = analogRead(sensor_pin);
  return sensor_reading;
}

void set_speed(int left_s, int right_s) {
  analogWrite(RO, right_s);
  analogWrite(LO, left_s);
}

void search_for_light() {
  int best_counter = 0;
  int best_ldr_value = 9999;
  leftcounter = 0;

  // Set the motor speeds to be the same
  set_speed(215, 215);
  
  while (leftcounter < 299) {
    int ldr_val = get_ldr_reading(middle_ldr);
    if (ldr_val < best_ldr_value) {
      best_ldr_value = ldr_val;
      best_counter = leftcounter;
    }
    Rotateright(0);
  }
  
  Stop();
  leftcounter = 0;
    
  while (leftcounter < best_counter) {
      Rotateright(0);
  }
  Stop();
}

void drop_detected() {
  Stop();
  delay(1000);
  set_speed(200,190);
  
  for (int i=0; i<6; i++) {
    backward();
    delay(1000);
    Stop();
    delay(300);
  }
}

void obstacle_detected() {
  set_speed(200,190);
  backward();
  delay(500);
}

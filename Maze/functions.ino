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

float get_distance() {
  delay(50);
  int distance = forward_sonar.ping_cm();
  delay(50);
  return distance;
}

/*void check_direction() {
  // Setup variables
  int first_zero = -1; // Keeps track of the first counter rotation to be 0
  int last_zero = -1; // Keeps track of the last counter rotation to be 0
  leftcounter = 0;

  // Set the motor speeds to be the same
  set_speed(215, 215);

  // Keep rotating until rotated 360 degrees
  while (leftcounter < 299) {
    // Read distance
    int my_distance = get_distance();

    // If the distance is greater than the current highest
    if (my_distance == 0) {
      if (first_zero < 0 && (leftcounter < 115 || leftcounter > 190)) {
        first_zero = leftcounter;
      }
      else if (leftcounter < 115 || leftcounter > 190) {
        last_zero = leftcounter;
      }
    }
    Rotateright(0); // Rotates clockwise on the spot
  }
  
  Stop(); // Stop rotating
  leftcounter = 0; // Reset the counter

  // Check if we are at a dead end
  if (first_zero < 0) {
    // Keep rotating until rotated 360 degrees
    while (leftcounter < 299) {
      // Read distance
      int my_distance = get_distance();
  
      // If the distance is greater than the current highest
      if (my_distance == 0) {
        if (first_zero < 0) {
          first_zero = leftcounter;
        }
        else if (leftcounter < 115 || leftcounter > 190) {
          last_zero = leftcounter;
        }
      }
      Rotateright(0); // Rotates clockwise on the spot
    }
    
    Stop(); // Stop rotating
    leftcounter = 0; // Reset the counter
  }
  
  int best_counter = (int) (first_zero + last_zero) / 2;

  // Keep rotating until we are facing the highest distance
  while (leftcounter < best_counter) {
      Rotateright(0);
  }
  Stop(); // Stop rotating
}*/

void check_direction() {
  // Setup variables
  int best_position = -1;
  int escapes = 0;
  leftcounter = 0;

  // Set the motor speeds to be the same
  set_speed(215, 215);

  // Keep rotating until rotated 360 degrees
  for (int i=0; i<4; i++) {
    leftcounter = 0;
    Rotateright(0); // Rotates clockwise on the spot
    while (leftcounter < 73) {
      // Do nothing
    }
    Stop();
    // Read distance
    int my_distance = get_distance();

    // If the distance is greater than the current highest
    if (my_distance == 0 && escapes == 0) {
      best_position = i;
      escapes++;
    }
    else if (my_distance == 0 && i > 1){
      best_position = i;
      escapes++;
    }
    
   
    delay(500);
  }
  
  Stop(); // Stop rotating
  leftcounter = 0; // Reset the counter

  // Keep rotating until we are facing the highest distance
  for (int i=0; i<best_position+1; i++) {
    leftcounter = 0;
    Rotateright(0); // Rotates clockwise on the spot
    while (leftcounter < 73) {
      // Do nothing
    }

    Stop();
    delay(500);
  }

  Stop(); // Stop rotating
}

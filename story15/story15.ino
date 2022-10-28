
#include <NewPing.h>

#define FRONT_TRIGGER_PIN  4 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define FRONT_ECHO_PIN     5 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define BOTTOM_TRIGGER_PIN  13 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define BOTTOM_ECHO_PIN     17 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing forward_sonar(FRONT_TRIGGER_PIN, FRONT_ECHO_PIN, MAX_DISTANCE); // Setup pins and max distance for forward facing sensor
NewPing down_sonar(BOTTOM_TRIGGER_PIN, BOTTOM_ECHO_PIN, MAX_DISTANCE); // Setup pins and max distance for downward facing sensor

int RF = 7;
int RB = 8;
int RO = 9;
int LO = 10;
int LF = 11;
int LB = 12;

int middle_ldr = A6; 
int left_ldr = A7; 
int right_ldr = A2; 

const int LEFT_FEEDBACK = 3;
const int RIGHT_FEEDBACK = 2;

volatile int leftcounter = 0;
volatile int rightcounter = 0;

int LEFT_SPD = 215;
int RIGHT_SPD = 150;

float front_distance = 150;
float down_distance = 1;
float last_measured = 400;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(RF, OUTPUT);    //rightmotor fowrards
  pinMode(RB, OUTPUT);    //rightmotor backwards
  pinMode(RO, OUTPUT);
  pinMode(LO, OUTPUT);
  pinMode(LF, OUTPUT);   //leftmotor forwards
  pinMode(LB, OUTPUT);   //leftmotor backwards

  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK), LeftMotorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK), RightMotorISR, RISING);
  
  analogWrite(RO, RIGHT_SPD);
  analogWrite(LO, LEFT_SPD);

  front_distance = forward_sonar.ping_cm();
  down_distance = down_sonar.ping_cm();

  search_for_light(); // Rotate to point at light source
}

// the loop function runs over and over again forever
void loop() {
  delay(50);
  // code for followin light
  int left_ldr_value = get_ldr_reading(left_ldr);
  int right_ldr_value = get_ldr_reading(right_ldr);
  int middle_ldr_value = get_ldr_reading(middle_ldr);
  if (left_ldr_value < right_ldr_value && left_ldr_value < middle_ldr_value){
    //turn more left
    set_speed(90, 255);
    forward();
  }
  if (right_ldr_value < left_ldr_value && right_ldr_value < middle_ldr_value){
    //turn more right
    set_speed(255, 50);
    forward();
  }
  if (middle_ldr_value < left_ldr_value && middle_ldr_value < right_ldr_value){
    //go straight
    set_speed(227, 140);
    forward();
  }

  // check for drop 
  if (down_distance - last_measured >= 6 && last_measured != 400) {
    set_speed(227,140);
    backward();
    delay(5000);
    Stop();
    delay(500);
    search_for_light();
    
  }

  //check for obstacle
  if (front_distance < 20 && front_distance > 0) {
    backward();
    delay(1000);
    Stop();
    search_for_light();
  }

  last_measured = down_distance;
  front_distance = forward_sonar.ping_cm();
  down_distance = down_sonar.ping_cm();
}
// check max forward while straight speed
//complete all bonuses in the morning
//test chain of rovers


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

const int LEFT_FEEDBACK = 3;
const int RIGHT_FEEDBACK = 2;

volatile int leftcounter = 0;
volatile int rightcounter = 0;

//int LEFT_SPD = 215;
//int RIGHT_SPD = 150;

int LEFT_SPD = 215;
int RIGHT_SPD = 215;

float front_distance = 150;
float down_distance = 1;
float last_measured = 400;

int best_counter = 0;
int best_ldr_value = 99e9;
bool searching = true;

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
}

// the loop function runs over and over again forever
void loop() {
  if (leftcounter < 299 && searching) {
    int ldr_val = get_ldr_reading(middle_ldr);
    if (ldr_val < best_ldr_value) {
      best_ldr_value = ldr_val;
      best_counter = leftcounter;
    }
    
    Rotateright(0);
  }
  else if (searching) {
    Stop();
    searching = false;
    leftcounter = 0;
  } else {
    if (leftcounter < best_counter) {
      Rotateright(0);
    } else {
      forward();
    }
  }
}

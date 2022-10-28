
#include <NewPing.h>

#define TRIGGER_PIN  4 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int RF = 7;
int RB = 8;
int RO = 9;
int LO = 10;
int LF = 11;
int LB = 12;

const int LEFT_FEEDBACK = 3;
const int RIGHT_FEEDBACK = 2;

volatile int leftcounter = 0;
volatile int rightcounter = 0;

int LEFT_SPD = 235;
int RIGHT_SPD = 190;

int start_time = 0;

float distance_measured = 150;

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

  distance_measured = sonar.ping_cm();
  distance_measured = 150;
}

// the loop function runs over and over again forever
void loop() {
  delay(50);

  forward();
  if (distance_measured < 20 && distance_measured > 0) {
    backward();
    delay(500);
    Stop();
    Turnleft(1400);
  }

  distance_measured = sonar.ping_cm();
}

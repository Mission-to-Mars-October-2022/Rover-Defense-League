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

int LEFT_SPD = 175;
int RIGHT_SPD = 120;

int start_time = 0;

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

  start_time = millis(); // Set the start time
  forward(); // Start the rover
}

// the loop function runs over and over again forever
void loop() {
  
   if (leftcounter > rightcounter) {
      LEFT_SPD = 100;
      RIGHT_SPD = 195;
   }
   
   if (rightcounter > leftcounter) {
      RIGHT_SPD = 110;
      LEFT_SPD = 185;
    
   }

   analogWrite(RO, RIGHT_SPD);    // turn the LED off by making the voltage LOW
   analogWrite(LO, LEFT_SPD);

   Serial.print("Left speed ");
   Serial.println(LEFT_SPD);
   Serial.print("Left counter ");
   Serial.println(leftcounter);
   
   Serial.print("Right speed ");
   Serial.println(RIGHT_SPD);
   Serial.print("Right counter ");
   Serial.println(rightcounter);
   
   //leftcounter = 0;
   //rightcounter = 0;

   if (rightcounter > 900) {
    Stop();
   }
  
}

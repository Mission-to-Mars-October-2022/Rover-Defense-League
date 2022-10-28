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

int LEFT_SPD = 210;
int RIGHT_SPD = 190;

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

}

// the loop function runs over and over again forever
void loop() {
  
   /*if (leftcounter > rightcounter) {
      LEFT_SPD = 100;
      RIGHT_SPD = 195;
   }
   
   if (rightcounter > leftcounter) {
      RIGHT_SPD = 110;
      LEFT_SPD = 185;
    
   } */

   //analogWrite(RO, RIGHT_SPD);    // turn the LED off by making the voltage LOW
   //analogWrite(LO, LEFT_SPD);

   for (int i = 0; i < 4; i++){ 
    forward();
    delay(1450);
    Stop();
    delay(500);
    Turnleft(1450);
    delay(500);
    }
  delay(5000);
}

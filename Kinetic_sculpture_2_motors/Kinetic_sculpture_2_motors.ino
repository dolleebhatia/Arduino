//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Using the easy stepper with your arduino
//use rotate and/or rotateDeg to controll stepper motor
//speed is any number from .01 -> 1 with 1 being fastest - 
//Slower Speed == Stronger movement
/////////////////////////////////////////////////////////////////

// for my steppers, it's 450 steps per inch

//#define DIR_PIN 4
//#define STEP_PIN 3

//#define DIR_PIN 12
//#define STEP_PIN 11

#define motor1Dir 4
#define motor1Step 3

#define motor2Dir 8
#define motor2Step 9




int stepsCounter;

int button = 7;

void setup() {
  Serial.begin(9600);
  pinMode(motor1Dir, OUTPUT);
  pinMode(motor1Step , OUTPUT);
   pinMode(motor2Dir, OUTPUT);
  pinMode(motor2Step , OUTPUT);
 
  
  
  pinMode(button, INPUT);
} 

void loop(){ 

  //rotate a specific number of degrees 
  rotateDeg(360, .5);
//  rotateDeg(360, .5);
//  rotateDeg(360, .5);
//  rotateDeg(360, .5);
 // delay(500);


  //rotate a specific number of microsteps (8 microsteps per step)
  //a 200 step stepper would take 1600 micro steps for one full revolution
//  if(digitalRead(button)==HIGH){
//  rotate(100, .1);
//  stepsCounter+=10;
//  delay(500);
//  Serial.println(stepsCounter);
//  }

//
//  rotate(-1600, .25); //reverse
//  delay(1000);
}

void rotate(int steps, float speed){
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (steps > 0)? HIGH:LOW;
  steps = abs(steps);

  digitalWrite(motor1Dir,dir); 

  float usDelay = speed;

  for(int i=0; i < steps; i++){
    digitalWrite(motor1Step , HIGH);
    delayMicroseconds(usDelay); 

    digitalWrite(motor1Step , LOW);
    delayMicroseconds(usDelay);
  }
  
   for(int i=0; i < steps; i++){
    digitalWrite(motor2Step , HIGH);
    delayMicroseconds(usDelay); 

    digitalWrite(motor2Step , LOW);
    delayMicroseconds(usDelay);
  }
  

  
  
} 

void rotateDeg(float deg, float speed){
  //rotate a specific number of degrees (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (deg > 0)? HIGH:LOW;
  digitalWrite(motor1Dir,dir); 

  int steps = abs(deg)*(1/0.225);
  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){
    digitalWrite(motor1Step, HIGH);
    delayMicroseconds(usDelay); 

    digitalWrite(motor1Step, LOW);
    delayMicroseconds(usDelay);
  }
  
  
  
  for(int i=0; i < steps; i++){
    digitalWrite(motor2Step, HIGH);
    delayMicroseconds(usDelay); 

    digitalWrite(motor2Step, LOW);
    delayMicroseconds(usDelay);
  }
  
 
  
}

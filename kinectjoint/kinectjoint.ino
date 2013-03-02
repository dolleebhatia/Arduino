#include <Servo.h> 

// declare both servos
Servo shoulder;
Servo elbow;

// setup the array of servo positions ❷
int nextServo = 0;
int servoAngles[] = {0,0};

void setup() {
  // attach servos to their pins ❸
  shoulder.attach(10);
  elbow.attach(9);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){ 
    int servoAngle = Serial.read();

    servoAngles[nextServo] = servoAngle;
    nextServo++;
    if(nextServo > 1){
      nextServo = 0;
    }

     shoulder.write(servoAngles[0]); 
    elbow.write(servoAngles[1]);
    Serial.println(servoAngles[1]); 

  }
}

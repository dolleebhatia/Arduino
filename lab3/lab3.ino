#include <Servo.h>




Servo servoMotor;
int servoPin = 2;

void setup() {
 Serial.begin(9600);
 
}

void loop() {
 
 int analogValue = analogRead(A0);
 Serial.println(analogValue);
  
 int servoAngle = map(analogValue, 0 , 1023, 0, 179);
servoMotor.write(servoAngle); 
  
}

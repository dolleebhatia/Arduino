#include <Servo.h>

//for Servo Motors.
//can go to sketch for import library
//go file xan get the example.

int sensorPin= A0;
int sensorValue = 0;

int servoPin = 2;
Servo servoMotor;

void setup(){
  Serial.begin(9600);
  servoMotor.attach(servoPin);
  
}
void loop(){
  sensorValue = analogRead(sensorPin);
  
  int servoAngle = map(sensorValue,0,1024,0,500);
  Serial.println(servoAngle);  
  delay(5);  
  //make the servo move that angle.
  servoMotor.write(servoAngle);
 
  
}

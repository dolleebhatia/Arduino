// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 

Servo myservo1;  // create servo object to control a servo 
  
 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
 
int potpin1 = 1;  // analog pin used to connect the potentiometer
int val1;    // variable to read the value from the analog pin 
 
 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 

  myservo1.attach(10);  // attaches the servo on pin 9 to the servo object
} 
 
void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  
  Serial.print(potpin);
   val1 = analogRead(potpin1);            // reads the value of the potentiometer (value between 0 and 1023) 
  val1 = map(val1, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  
  myservo.write(val);                  // sets the servo position according to the scaled value 
   myservo1.write(val1);       
  delay(15);                           // waits for the servo to get there 
} 

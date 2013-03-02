
#include <Servo.h>


// these constants won't change:
const int xPin = 2;     // X output of the accelerometer
const int yPin = 3;     // Y output of the accelerometer
int val;
int valAverage = 0;
int valx;
int valxAverage = 0;


const int ledPin = 10;  
int yaxisValue = 0;


Servo myservo;  // create servo object to control a servo 
void setup() {
  // initialize serial communications:
  Serial.begin(9600);
  // initialize the pins connected to the accelerometer
  // as inputs:
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
    
    
     pinMode(ledPin, OUTPUT);
 // pinMode(greenLED, OUTPUT);
}

void loop() {
 // yaxisValue = analogRead(A0);
 
 
  // variables to read the pulse widths:
  int pulseX, pulseY;
  // variables to contain the resulting accelerations
  int accelerationX, accelerationY;
  
  // read pulse from x- and y-axes:
  pulseX = pulseIn(xPin,HIGH);  
  pulseY = pulseIn(yPin,HIGH);
  
  // convert the pulse width into acceleration
  // accelerationX and accelerationY are in milli-g's: 
  // earth's gravity is 1000 milli-g's, or 1g.
  accelerationX = ((pulseX / 10) - 500) * 8;
  accelerationY = ((pulseY / 10) - 500) * 8;

  // print the acceleration
 Serial.print(accelerationX);
 // print a tab character:
 Serial.print("\t");
 Serial.print(accelerationY);
 Serial.println();
  //for is for takeing the average for make the servo smoothly.
  for(int i = 0; i < 5; i++){
  val = map(accelerationY,-1200 , 1200, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
//can put a if stament here.
valAverage = valAverage + val;  
}
// if value is too high change number you divide by
valAverage = valAverage / 5;
  myservo.write(val);   // sets the servo position according to the scaled value 
 // valAverage = 0;
  delay(100);


//for LEDS
 for(int i = 0; i < 5; i++){
  valx = map(accelerationX,-1200 , 1200, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
//can put a if stament here.
valxAverage = valxAverage + val;  
}
// if value is too high change number you divide by
valxAverage = valxAverage / 5;
//Serial.println(valx);



  yaxisValue = analogRead(yPin);    
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  delay(valx);          
  // turn the ledPin off:        
  digitalWrite(ledPin, LOW);   
  // stop the program for for <sensorValue> milliseconds:
  delay(valx);  
//Serial.println(yaxisValue);
//Serial.println("accelerationX " accelerationX);
//Serial.print("accelerationY " accelerationY);


}




////commented out all unnecessary println's
#include <Servo.h>
Servo myservo;

boolean movedCenter = false;
boolean movedLeft = false;

int val; // outgoing ADC value
int distance = 0; 
int threshold = 8; //how close the cat can come
int closeTime = 20000; //1 min  delay on closing lid
int startTime;

int leftButton = 2;
int buttonState;

void setup()
{
  Serial.begin(9600);
  startTime = millis();
  myservo.attach(9);  
  myservo.write(90);
  pinMode(leftButton, INPUT);
}

void loop()
{
  //Linearize the Sharp IR reading
  val = analogRead(0);
//  Serial.print("Analog Value =\t");
  distance = (2914 / (val + 5)) - 1;
  Serial.println(distance);
  delay(10);
  


  if (distance < threshold && buttonState == LOW)
  {

   // Serial.println(distance);
    myservo.write(0);
  //  Serial.println("open the lid"); 
  }
  else
  {
    closeLid();
  }
   manualClose();
   Serial.flush();
}

void closeLid()
{
  int ahora = millis();
  if (ahora - startTime > closeTime) 
  {
    startTime = ahora;
    myservo.write(90);
 //   Serial.println("close the lid");
  } 
  
}

void manualClose()
{
  //we may need to add in 'debounce code for on/off effect
  buttonState = digitalRead(leftButton);

  if (buttonState == HIGH)
  {
  myservo.write(90);
  //Serial.println("close lid by button");  
  }
} 

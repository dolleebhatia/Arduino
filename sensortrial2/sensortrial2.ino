const int pingPin = 6;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(2, OUTPUT);  
  pinMode(7, OUTPUT);   
  pinMode(9, OUTPUT);  
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
 // Serial.print(inches);
  //Serial.print("in, ");
  //Serial.print(cm);
  //Serial.print("cm");


  
  if(cm>190){
      digitalWrite(3, HIGH); 
      digitalWrite(12, LOW); 
      digitalWrite(7, LOW); 
      digitalWrite(2, LOW); 
      digitalWrite(9, LOW); 
      digitalWrite(11, LOW);
      digitalWrite(13, LOW);       
      //...and so on
  }
  
   if(cm>100 && cm<190){
      digitalWrite(3, HIGH);
      digitalWrite(12, HIGH); 
      digitalWrite(7, LOW); 
      digitalWrite(2, LOW); 
      digitalWrite(9, LOW); 
      digitalWrite(11, LOW);      
     //turn the rest low 
  }
  
  if(cm>60 && cm<100){
      digitalWrite(3, HIGH); 
      digitalWrite(12, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(2, LOW); 
      digitalWrite(9, LOW); 
      digitalWrite(11, LOW);
      
     //turn the rest low 
  }
  
  if(cm>50 && cm<80){
      digitalWrite(3, HIGH); 
      digitalWrite(12, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(2, HIGH); 
      digitalWrite(9, LOW); 
      digitalWrite(11, LOW);
      digitalWrite(13, LOW); 
     //turn the rest low 
  }
  
    if(cm>20 && cm<50){
      digitalWrite(3, HIGH); 
      digitalWrite(12, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(2, HIGH); 
      digitalWrite(9, LOW); 
      digitalWrite(11, LOW);
      digitalWrite(13, LOW); 
     //turn the rest low 
  }
  
  if(cm>20 && cm<60){
      digitalWrite(3, HIGH); 
      digitalWrite(12, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(2, HIGH); 
      digitalWrite(9, HIGH); 
      digitalWrite(11, LOW);
      digitalWrite(13, LOW); 
     //turn the rest low 
  }
  
  if(cm>5 && cm<20){
      digitalWrite(3, HIGH); 
      digitalWrite(12, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(2, HIGH); 
      digitalWrite(9, HIGH); 
      digitalWrite(11, HIGH);
      digitalWrite(13, HIGH); 
     //turn the rest low 
  }
    Serial.println(cm);
  delay(100);
}



long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

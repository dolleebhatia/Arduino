
 
 
void setup()
{
  Serial.begin(9600);
//  pinMode(switchPin,INPUT);
  pinMode(A0,INPUT);
  pinMode(A1, INPUT);
}
 
 
void loop()
{
    int sensorValue = analogRead(A0);
     Serial.print(sensorValue);
     Serial.print(",");
    sensorValue = analogRead(A1);
     Serial.print(sensorValue);
     Serial.print(",");
//    sensorValue = digitalRead(switchPin);
     Serial.println(sensorValue);
     Serial.flush(); 
 }

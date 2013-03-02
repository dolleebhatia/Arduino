#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
Servo myservo;


int keyPressed = 0;
int inByte = 0; 


boolean movedRight = false;
boolean movedCenter = false;
boolean movedLeft = false;

//byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x85, 0x70 };
//byte mac[] = {0x02, 0xAA, 0xBB, 0xCC, 0x00, 0x1A }; //marlon's car
//byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x13, 0x80 }; //dave
//byte mac[] = {0x00, 0xAD, 0xBE, 0xEF, 0xED, 0x9A }; //antonious
byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x7E, 0xE9 }; //evan

//IPAddress server (128, 122, 157, 182); // stu.itp.nyu.edu server
IPAddress server(108,166,81,215); //rackspace server
int port = 12002;
EthernetClient client;

void setup()   { 
  
  Ethernet.begin(mac);
  Serial.begin(9600);
   myservo.attach(9);
  delay(1000);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  } 
  Serial.println("Ethernet ready");
  serverConnect();
}


void serverConnect(){
  Serial.println("connecting to remote server...");
  if (client.connect(server, port)) {
    Serial.println("connected to remote server");
    client.println('A');
  } 
  else {
    Serial.println("remote connection failed");
  }
}

void loop() {
 // serverConnect();
  
  // if we get a valid byte, read analog ins:
  if (client.available()) {
    // get incoming byte:
    inByte = client.read();
    Serial.print(inByte);
//delay(1000);
//
//switch(inByte){
//  
//  
//   case '1': 
//      myservo.write(179);
//        Serial.println("Attempting to move Servo Left.."); 
//        movedLeft = true; 
//      break;
//    case '2': 
//     myservo.write(90);
//         Serial.println("Attempting to move Servo Center.."); 
//         movedCenter = true;
//      break;
//    case '3': 
//     myservo.write(0);
//         Serial.println("Attempting to move Servo Right.."); 
//         movedRight = true;
//      
//      break;
//  
  
//}



//   if (inByte == 49 && movedLeft == false) {
//        myservo.write(179);
//        Serial.println("Attempting to move Servo Left.."); 
//        movedLeft = true;
//      }
//      
//    else  if (inByte == 50 && movedCenter == false ) {
//     
//         myservo.write(90);
//          Serial.println("Attempting to move Servo Center.."); 
//         movedCenter = true;
//        // keyPressed = 0;
//      }
//      
//     else if (inByte == 51 && movedRight == false) {
//         myservo.write(0);
//         Serial.println("Attempting to move Servo Right.."); 
//          movedRight = true;
//      }

moveCamera();  
 client.flush();
  }

}


void moveCamera(){
 
    if (inByte == 49 && movedLeft == false) {
        myservo.write(179);
        Serial.println("Attempting to move Servo Left.."); 
        movedLeft = true;
      }
      
    else  if (inByte == 50 && movedCenter == false ) {
     
         myservo.write(90);
          Serial.println("Attempting to move Servo Center.."); 
         movedCenter = true;
        // keyPressed = 0;
      }
      
     else if (inByte == 51 && movedRight == false) {
         myservo.write(0);
         Serial.println("Attempting to move Servo Right.."); 
          movedRight = true;
      }
 }



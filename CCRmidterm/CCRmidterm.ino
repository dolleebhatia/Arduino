#include <SPI.h>
#include <Ethernet.h>
#include <TextFinder.h>
#include <Servo.h>
Servo myservo;


boolean Connected = false;
char message[500];

int keyPressed = 0;
int counter = 2000;
int responseSize = 0;
boolean Read = true;

boolean movedRight = false;
boolean movedCenter = false;
boolean movedLeft = false;

byte mac[] = {  
  0x02, 0xAA, 0xBB, 0xCC, 0x00, 0x1A };
IPAddress server(128,122,157,182); //stu.itp.nyu.edu
EthernetClient client;



void setup() {
   Serial.begin(9600);
  myservo.attach(9);
  
  // start the serial library:
  Serial.begin(9600);
  // start the Ethernet connection
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}


void connectRead() {
  if(!Connected){
  
 Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /~db2497/sinatra/main_agi/digitinfo HTTP/1.1");
    client.println("Host: stu.itp.nyu.edu");
    client.println();  
    Connected = true;
//    responseSize = 0;

 } 

  else {
    Serial.println("connection failed");
  }

}
}


void readPage() {
 // memset( message, 0, 1000 );
  
   
 if(Read){
    
  
   
    if (client.available()) {
     // Serial.print("reading.. "); 
      
      char c = client.read();
     
      
    //  Serial.print(c);
        message[responseSize] +=c;
      responseSize++;      
      

      if (c == '*') {
        Serial.println();
        Serial.print("size of file is ");    
        Serial.println(responseSize); 
       for (int i = 0; i < responseSize; i++){
         //    Serial.print(message[i]);
         if (message[i] == '^'){
          
           if(message[i+1] == '^'){
              
              keyPressed = int(message[i+2]);
              Serial.print("keypressed is ");     
              Serial.println(keyPressed); 
              Read = false; 
              
             
               //    }
         }
        }
    }  
            
    }
              if (!Read) {
               //  responseSize=0;
              
              client.stop();
              Serial.println("disconnecting.");
              client.flush();
         
              delay (2000);
            
   //  responseSize =0;

                Serial.println();
                Read = true;
                Connected = false;
            //   responseSize=0;
             
           
              }

   
  
 }
}
}



void moveCamera(){
 
    if (keyPressed == 49 && movedLeft == false) {
        myservo.write(179);
        Serial.println("Attempting to move Servo Left.."); 
        movedLeft = true;
      }
      
    else  if (keyPressed == 50 && movedCenter == false ) {
     
         myservo.write(90);
          Serial.println("Attempting to move Servo Center.."); 
         movedCenter = true;
        // keyPressed = 0;
      }
      
     else if (keyPressed == 51 && movedRight == false) {
         myservo.write(0);
         Serial.println("Attempting to move Servo Right.."); 
          movedRight = true;
 
      }
 
 message[responseSize] = 0;
// Serial.println("Clearing"); 
 
 }




void loop()
{
 // delay (3000); 
 connectRead();
  readPage(); 
 moveCamera();
   
// responseSize=0;
  
}
 

  
  


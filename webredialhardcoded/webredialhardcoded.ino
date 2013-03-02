

/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <TextFinder.h>

boolean Connected = false;
char message[1000];
int responseSize = 0;
int keyPressed = 0;
int counter = 2000;

boolean movedRight = false;
boolean movedCenter = false;
boolean movedLeft = false;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  
  0x02, 0xAA, 0xBB, 0xCC, 0x00, 0x1A };
IPAddress server(128,122,157,182); //stu.itp.nyu.edu

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
//TextFinder finder( message );


void setup() {
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

void loop()
{
  
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {


    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /~db2497/sinatra/main_agi/digitinfo HTTP/1.1");
    client.println("Host: stu.itp.nyu.edu");
    client.println();
    delay (4000);

  } 

  else {
    //    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }


  // if there are incoming bytes available
  // from the server, read them and print them:


 // while(true){
    
    if (client.available()) {
      char c = client.read();
    
   //  Serial.print(c);
      //delay (000);
     
      message[responseSize] +=c;
      responseSize++;
       Serial.println("still here" );
       Serial.println(responseSize);  
      // delay (8000);
        //client.flush();
      //Serial.println("disconnecting.");
     //client.stop(); 
    }
//  }
 // Serial.println(responseSize); 
   keyPressed = int(message[306]);
  Serial.print("keypressed is ");     
   Serial.println(keyPressed); 
//    client.flush();
//     Serial.println("disconnecting.");
//     client.stop(); 
   
 

 

 //   for (int i = 0; i < responseSize; i++){
      // Serial.print(message[i]);
   //   if (message[i] == '*'){
     //   if(message[i+1] == '*'){
       //   keyPressed = int(message[i+2]);
          
         //  delay (1000); 
         // i = 1000;
       //  break;
         
          
           
          
        //}
      //}
    //}
         
          
      
          
       
      
      //delay (1000); 
      // Serial.println();

     // Serial.println(responseSize); 
    //  break;

    
  
  
  


  // for (int i = 0; i < counter; counter++){

  //    if (keyPressed == 49 && movedLeft == false) {
  //       Serial.println("1"); 
  //       //move the camera
  //       movedLeft = true;
  //       keyPressed = 0;
  //    }
  //    
  //  else  if (keyPressed == 50 && movedCenter == false) {
  //       Serial.println("2");
  //        movedCenter = true;
  //       keyPressed = 0;
  //    }
  //    
  //   else if (keyPressed == 51 && movedRight == false) {
  //       Serial.println("3");
  //        movedRight = true;
  //       keyPressed = 0;
  //    }
  // }

  // I am going to do something if keyPressed == lastkeypressed don't do anything 



  // do nothing forevermore:
  // for(;;)
  //;
  //}
  //}

}






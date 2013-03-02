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

byte mac[] = {  
  0x02, 0xAA, 0xBB, 0xCC, 0x00, 0x1A };
IPAddress server(128,122,157,182); //stu.itp.nyu.edu


EthernetClient client;



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

  connectRead();
  readPage();   
    
}
 
void readPage() {
  
 while(true){

    if (client.available()) {
     // Serial.print("reading.. "); 
      char c = client.read();
       Serial.print(c);
      message[responseSize] +=c;
      responseSize++;      
    }

      if (responseSize > 305) {
        Serial.println();
        Serial.print("size of file is ");    
        Serial.println(responseSize); 
        for (int i = 0; i < responseSize; i++){
          //   Serial.print(message[i]);
          if (message[i] == '*'){
            if(message[i+1] == '*'){
              
              keyPressed = int(message[i+2]);
              Serial.print("keypressed is ");     
              Serial.println(keyPressed); 
             
             
             
              client.flush();
              client.stop();
              Serial.println("disconnecting.");
                Serial.println();
              delay (10000);

            }
          }
        }


        break; 
        // 
      }
    }
  }


void connectRead() {
  
 Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /~db2497/sinatra/main_agi/digitinfo HTTP/1.1");
    client.println("Host: stu.itp.nyu.edu");
    client.println();  

 } 

  else {
    Serial.println("connection failed");
  }

}

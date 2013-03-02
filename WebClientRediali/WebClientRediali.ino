

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

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0x02, 0xAA, 0xBB, 0xCC, 0x00, 0x1A };
IPAddress server(128,122,157,182); //stu.itp.nyu.edu

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
TextFinder finder( client );

void setup() {
  // start the serial library:
  Serial.begin(9600);
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(3000);


}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    //char c = client.read();
    // character array 
   
    //Serial.print(c);
    
    finder.find("key "); // skip past this 
    long value = finder.getValue(); // get numeric value
    Serial.println(value);
    
    
  }
 

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    delay (3000);
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}

 
 void connector(){
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
    
  } 
  
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
    }
 }

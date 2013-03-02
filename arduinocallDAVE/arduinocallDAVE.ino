/*
This code is designed to generate a call when ever a button is pushed.  The httpDelay
variable will determine how long the code should wait before generating another call.
This is so a flaky button won't generate dozens of calls to my phone.

The HTTP_ACTIVE and HTTP_IDLE states are used to make sure that you don't start a request
before the last request has finished.
*/

//state constants
#define HTTP_ACTIVE 10
#define HTTP_IDLE 20
#include <Ethernet.h>
#include <SPI.h>
 

//setup          00    AD    BE    EF    ED    1A
byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x13, 0x80 }; //DAVE'S CARD
//IPAddress server (128, 122, 157, 182); // stu.itp.nyu.edu web server
IPAddress server(108,166,81,215); //rackspace server



//client stuff
char httpCommand[] ="GET /~dolleeb/sinatra/callbob?callnumber=19174365310 HTTP/1.0";
EthernetClient client;
byte httpState = HTTP_IDLE;
int httpDelay = 5000; //wait at least this long in millis before sending another request
unsigned long connectTime = 0;

//button stuff
const int buttonPin = 5;
int buttonState = 0;

void setup() {
    Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("ready.");
}

void loop() {
  //read input from server, if any.
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  //check button, only read if there are no active http connections and we're past minimum delay
  if (httpState == HTTP_IDLE && pastHttpDelay()) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      serverConnect();
    }

  }
  //close client if disconnected
  if (!client.connected() && httpState == HTTP_ACTIVE) {
    client.stop();
    httpState = HTTP_IDLE;
    Serial.println();
    Serial.println("disconnected.");
  }
}

boolean pastHttpDelay(){
  if ((millis() - connectTime) > httpDelay) {
    return true;
  }
  else {
    return false;
  }
}

void serverConnect(){
  Serial.println("connecting to server");
  if (client.connect(server, 80)) {
    httpState = HTTP_ACTIVE;
    connectTime = millis(); //when did we connect?
    Serial.println("connected");
    client.println(httpCommand);
    client.println();
  }
  else {
    httpState = HTTP_IDLE;
    Serial.println("connection failed");
  }
}

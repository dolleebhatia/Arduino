//PRACTICE LOOP CODE
#include <SPI.h>
#include <Ethernet.h>
#include <String.h>
#include <TextFinder.h>
#include <Stepper.h>
#define PIN_HIGHBIT (3)
#define PIN_LOWBIT  (2)
//#define PIN_PWR     (5)
#define BAUDRATE    (9600)
#define DEBUG         (1)

int state, prevState = 0, count = 0;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
int encoderStates[4][4] = {
  {  
    0, -1,  1,  0                               }
  ,
  {  
    1,  0,  0, -1                               }
  ,
  { 
    -1,  0,  0,  1                               }
  ,
  {  
    0,  1, -1,  0                               }
  ,
};

// initialize the stepper library on pins 8 through 11:
Stepper stepperY(stepsPerRevolution, 7, 6);
Stepper stepperX(stepsPerRevolution, 5, 4);
int currentX;
int currentY;

boolean drew = false;
String incomingString;
String command;
String task;
String prop1, prop2, prop3, prop4;

//ETHERNET STUFF
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(128,122,157,182); //stu.itp.nyu.edu

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

String commandAr[10];
String previousComm = "a";
String comm;
boolean addToString;
boolean stringAdded = false;
String tweetString;
boolean Connected = false;
boolean Read = true;
long counter; 
int tweetCounter;

void setup() {
  // set the speed at 60 rpm:
  stepperY.setSpeed(60);
  stepperX.setSpeed(60);
  // initialize the serial port:
  Serial.begin(BAUDRATE);

  //encoder part:
  pinMode(PIN_HIGHBIT, INPUT);
  pinMode(PIN_LOWBIT, INPUT);
  //pinMode(PIN_PWR, OUTPUT);
  //digitalWrite(PIN_PWR, LOW);
  digitalWrite(PIN_LOWBIT, HIGH);
  digitalWrite(PIN_HIGHBIT, HIGH);

  //reset switches

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  //Serial.println(digitalRead(3));

  //ETHERNET STUFF!
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  counter = 0;
}

void loop() {
  
  //CONNECT TO STUFF!
  connector();
  readData();
  //Serial.println(stringCreated);
    
  if (String(previousComm) == String(command)) {
    command = "";
  }
  //Serial.println("command " + command);

  // Check if there's incoming serial data.
/*
  while (Serial.available() > 0) {
    // Read a byte from the serial buffer.
    delay(10);
    char incomingByte = (char)Serial.read();
    incomingString += incomingByte;
    Serial.println("incoming: " + incomingString);
    if (incomingByte == ')') {
      command = incomingString;
      incomingString = "";
    }
    else {
      command = "0";
    }
    Serial.println("command " + command);
  }*/

  //this part of the code parses the command
  incomingString = "";
  int start = command.indexOf('(');
  int firstComma = command.indexOf(',');
  int secondComma = command.indexOf(',', firstComma+1);
  int thirdComma = command.indexOf(',', secondComma+1);

  task = command.substring(1, start);
  //first value
  prop1 = String(command.substring(start+1, firstComma));
  int value, value2, value3, value4;
  char carray[6];
  prop1.toCharArray(carray, sizeof(carray));
  value = atoi(carray);
  //second value
  prop2 = command.substring(firstComma + 1, secondComma);
  prop2.toCharArray(carray, sizeof(carray));
  value2 = atoi(carray);
  //third value
  prop3 = command.substring(secondComma + 1, thirdComma);
  prop3.toCharArray(carray, sizeof(carray));
  value3 = atoi(carray);
  //fourth value
  prop4 = command.substring(thirdComma + 1, command.length() -1);
  prop4.toCharArray(carray, sizeof(carray));
  value4 = atoi(carray);

  delay(10);

previousComm = command;
  //unknown command:
  if (task != "" && task != "circle" && task != "rect" && task != "move" && task != "reset" && task != "line") {
    Serial.println("Available Commands are: ");
    Serial.println("reset()");
    Serial.println("move(int x, int y)");
    Serial.println("line(int x1, int y1, int x2, int y2)");
    Serial.println("rect(int x, int y, int w, int h)");
    Serial.println("circle(int x, int y, int r)");
    task = "";
  }

  //draw circle
  if (task == "circle") {
    moveToPos(value, value2);
    drawCircle(value3);

    command = "";
    incomingString = "";
  }

  if (task == "rect") {
    moveToPos(value, value2);
    moveToPos(value3, 0);
    moveToPos(0, value4);
    moveToPos(-value3, 0);
    moveToPos(0, -value4);
    command = "";
  }

  if (task == "reset") {
    reset();
    command ="";
  }
  if (task == "move") {
    delay(10);
    moveToPos(value, value2);
    command = "";
  }
  if (task == "line") {
    drawLine(value, value2, value3, value4);
    command = "";
  }

  command = "";

  //encoder part:
  state = (digitalRead(PIN_HIGHBIT) << 1) | digitalRead(PIN_LOWBIT);
  count += encoderStates[prevState][state];
  if (state != prevState) {
    Serial.println(count, DEC);
  }
  prevState = state;
  //stringCreated = false;
}

void drawCircle(int r) {
  int stepX = 0;
  int stepY = 0;
  //if (currentX >= r && currentY >= r) {
  for (int i = 4; i < 360 ; i +=4) {
    stepX = r*cos(radians(i-4)) - r*cos(radians(i));
    stepY = r*sin(radians(i-4)) - r*sin(radians(i));
    stepperX.step(int(stepX + .5));
    stepperY.step(int(stepY + .5));
    // }
  }
}

void reset() {
  while (digitalRead(3) == LOW) {
    stepperX.step(-1);

  }
  currentX = 0;
  while (digitalRead(2) == LOW) {
    stepperY.step(-1);
  }
  currentY = 0;
}

void moveToPos(int x, int y) {
  stepperX.step(x);
  stepperY.step(y);
}

void drawLine(int x, int y, int x2, int y2) {
  moveToPos(x, y);
  float m = (y2 - y)/(x2 - x);
  int stepY;
  for (int i = x+10 ; i < x2 ; i +=10) {
    stepY = int((m * i + (y2-m*x2)) - (m*(i-10) + (y2-m*x2)));
    stepperX.step(10);
    stepperY.step(stepY);
  }
}

void connector(){
 if(!Connected){ 
  //delay(250);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /~pmd299/twitter/twitterSearch.php HTTP/1.1");
    client.println("Host: stu.itp.nyu.edu");
    client.println();
    Connected = true;
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
}

void readData(){
  if(Read){
  // if there are incoming bytes available 
  // from the server, read them;
  if (client.available()) {
    //read data from client
    char c = client.read();
   
    //if newline is read, creat tweetString; if not add value of c to tweetString     
    if(c == '\n'){
      tweetString = "";
    }else{
      tweetString += c;
  }
  
    //if tweetString ends with *, add command string to command array and empty tweetString 
    if(tweetString.endsWith(")*")){
           command = tweetString;
           tweetString = ""; 
           Serial.println("command = " + command);
           Read = false;     
        }
    }
    
  // if the server's disconnected, stop the client:
  if (!Read) {
    Serial.println();
    Serial.println("disconnecting.");
    client.flush();
    client.stop();
    Connected = false;
    Read = true;
    // do nothing forevermore:
    //for(;;)
    //  ;
  }
 }
}





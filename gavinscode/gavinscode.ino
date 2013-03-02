#include
#include
////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
byte ip[] = {
128,122,151,150}; //ip address to assign the arduino
byte server[] = {
72,52,158,245}; //ip Address of the server you will connect to

//The location to go to on the server
//make sure to keep HTTP/1.0 at the end, this is telling it what type of file it is
String location = "/~benturne/other/testtwitterapi4.php /HTTP/1.0";

//NYU WAP subnet mask is 255.255.252.0
byte subnet[] = {
255, 255, 252, 0 };

// if need to change the MAC address for a different arduino shield
byte mac[] = {
0x90, 0xA2, 0xDA, 0x00, 0x6E, 0x2F };
EthernetC Client;

Client client(server, 80); // port 80 is typical www page

////////////////////////////////////////////////////////////////////////

//these are the pins that the scent dispensers are connected to
int scentPins[] = {
2, 5, 7, 9};
char inString[32]; // string for incoming serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?

void setup(){
Ethernet.begin(mac, ip);
Serial.begin(9600);

//turn on scent pins
for (int i = 0; i &lt; 4; i ++){
pinMode(scentPins[i], OUTPUT);
}
}

void loop(){
String pageValue = connectAndRead(); //connect to the server and read the output
Serial.println(pageValue); //print out the findings.
delay(10000); //wait 10 seconds before connecting again
}

String connectAndRead(){
//connect to the server
Serial.println("connecting...");
if (client.connect()) {
Serial.println("connected");
client.print("GET ");
client.println(location);
client.println();
//Connected - Read the page
return readPage(); //go and read the output
}
else{
return "connection failed";
}
}

String readPage(){
//read the page, and capture &amp; return everything between ' stringPos = 0;
memset( &amp;inString, 0, 32 ); //clear inString memory

while(true){
if (client.available()) {
char c = client.read();

if (c == '*' ) { //'*' is our begining character
startRead = true; //Ready to start reading the part
}
else if(startRead){
if(c != 'b'){ //'b' is our ending character
inString[stringPos] = c;
//check if the substring is 1 or 0
if ( c == '1'){
Serial.println(scentPins[stringPos] + " is the current string position");
digitalWrite(scentPins[stringPos], HIGH);
Serial.println("Sending HIGH on " + scentPins[stringPos]);
delay(200);
digitalWrite(scentPins[stringPos], LOW);
Serial.println("Sending LOW on " + scentPins[stringPos]);
delay(1000);
}
else {
Serial.println("This pin will not be turned HIGH");
}
stringPos++;
}
else{
//got what we need here! We can disconnect now
startRead = false;
client.stop();
client.flush();
Serial.println("disconnecting.");
return inString;
}
}
}
}
}

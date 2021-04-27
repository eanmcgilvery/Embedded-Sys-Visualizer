#include <SPI.h>
#include <WiFiNINA.h>
#include "vector.hpp"

// WIFI Settings 
const char ssid[] = "Emac";//"Ebola-Take-The-Wheel"; //"FiOS-WDRJY";          // Change this to your Wifi settings
const char pass[] = "eanisagod"; //"way79mouth4146pay";  //"St4yS3cure1";   // Change this to your Wifi settings 
int status = WL_IDLE_STATUS; // Used to check connection Statuses 
WiFiClient client;


// Server Functions and Vars
const byte serverIP[] = {107, 221, 75, 87};
void submitGetRequest();
void setupWifi();
Vector<char> commands;
Vector<char> parsedCommands;
Vector<char> lastModified;

void decideCommand(int i);
bool parse();

// Right Motor Pins
const int enA = 10;
const int in1 = 4;
const int in2 = 3;

// Left Motor Pins
const int enB = 9;
const int in3 = 2;
const int in4 = 5;

int speed;
bool notRan;
/*================MOVEMENT FUNCTIONS===================*/
void moveForward();
void moveBackward();
void halt();
void turnLeft();
void turnRight();

/*================TESTING FUNCTIONS====================*/
void back_and_forth(int speed);
void go_in_loop();
void spinMoveBaby();

void printWifiData();
bool pingTest();

// SETUP OF ALL VARIABLES AND CONNECTIONS
void setup() 
{
  Serial.begin(9600);
  setupWifi();
  // Attempt to ping Google for a network sanity check
  while(!pingTest());

  // Setup Motor Pins to be output
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Variable to ensure that the User's code is only executed once per change
  notRan = true;
  
  speed = 255; // NOTE: range from 0 - 255
  for(int i = 0; i < 9; i++)
    lastModified.push_back('0');
}

void loop() 
{
  submitGetRequest();
  
  if(parse())
  {
    Serial.println(parsedCommands.size());
    for(int index = 0; index < parsedCommands.size(); index++)
    {
      decideCommand(index);
      delay(1000);
    }
    halt();
  } 

  commands.clear();
  notRan = false;
}

void moveForward()
{
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward()
{
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void halt()
{
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(500);
}

void turnLeft()
{
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    delay(1000);

    halt();
}
void turnRight()
{
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    delay(1000);

    halt();
}

/* TESTING FUNCTIONS */
void back_and_forth(int speed)
{

  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(3500);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(3500);
}

void go_in_loop()
{
  for(int i = 0; i < 4; i++)
  {
    moveForward();
    delay(2000);
    turnLeft();
  }
}

void spinMoveBaby()
{
  for(int i = 75; i <=250; i+=15)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  
    delay(1000);
  }
}

void printWiFiData() 
{

  IPAddress ip = WiFi.localIP();

  Serial.print("IP address : ");

  Serial.println(ip);

  Serial.print("Subnet mask: ");

  Serial.println((IPAddress)WiFi.subnetMask());
}

bool pingTest()
{
  Serial.println("Pinging Google...");

  int pingResult = WiFi.ping("www.google.com");

  if (pingResult >= 0) 
  {
    Serial.print("SUCCESS! RTT = ");
    Serial.print(pingResult);
    Serial.println(" ms");
  } 
  else 
  {
    Serial.print("FAILED! Error code: ");
    Serial.println(pingResult);
  }

  return true;
}

void setupWifi()
{
 int connectionAttempts = 0;

  // Try to establish a WIFI Connection
  while ( status != WL_CONNECTED) 
  {
    connectionAttempts++;
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    Serial.print("Attempt #");
    Serial.println(connectionAttempts);
    
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // Wait 10 seconds for connection:
    delay(10000);
    if(status != WL_CONNECTED)
        Serial.println("Connection failed... Attempting Again");
  }
  Serial.println("CONNECTION SUCCESS!");
  
}

void submitGetRequest()
{
  setupWifi();
  if (client.connect(serverIP, 80)) 
  {
    Serial.println("Connected to Server!");
    Serial.println("Getting Commands from server...");
    client.println("GET / HTTP/1.1");
    client.println();
    
    // Delay the program execution so we can wait for a response from 
    //  the server.
    delay(2000);
    while(client.available())
    {      
      commands.push_back(client.read());
     // char c = client.read();
     // Serial.print(c);
    } 
    commands.display_contents();
  }
  else
  {
      Serial.println("SERVER CONNECTION FAILED");
  }
  client.stop();
}

bool parse()
{   
  parsedCommands.clear();
  bool flag = false;
  Serial.println();
  Serial.println("COMMAND VEC SIZE");
  Serial.println(commands.size());
  for(int i = 0; i < commands.size(); i++)
  {    
    // Only go through and grab the commands from the Message
    if(commands[i] == '>' && !flag)
    {
      Serial.print("Commands:");
      Serial.println(commands[i]);
      // We saw the first '>'
      flag = true;
      i++;
      // Begin by grabbing timestamp
      for(; commands[i] != '<'; i++)
      {
        parsedCommands.push_back(commands[i]);
      }

      Serial.println("PARSE SIZE: " + parsedCommands.size());
      // If the message is new, update our Timestamp and continue parsing
      if(parsedCommands > lastModified)
      {
        lastModified = parsedCommands;
        lastModified.display_contents();
      }
      // Message isn't new, so return 
      else
        return false;

      // Clear our the Vector so we can use it to just hold the Movement commands
      parsedCommands.clear();
      i++;
    }

    if(flag)
      parsedCommands.push_back(commands[i]);
  }
    parsedCommands.display_contents();
    return true;
}

void decideCommand(int i)
{
  if(parsedCommands[i] == 'R')
    turnRight();
  else if (parsedCommands[i] == 'L')
    turnLeft();   
  else if (parsedCommands[i] == 'F')
    moveForward();
  else if (parsedCommands[i] == 'B')
    moveBackward();
}

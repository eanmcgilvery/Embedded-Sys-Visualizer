#include <SPI.h>
#include <WiFiNINA.h>

// WIFI Settings 
const char ssid[] = "Emac";      // Change this to your Wifi settings
const char pass[] = "eanisagod"; // Change this to your Wifi settings 
int status = WL_IDLE_STATUS; // Used to check connection Statuses 


// Right Motor Pins
const int enA = 10;
const int in1 = 4;
const int in2 = 3;

// Left Motor Pins
const int enB = 9;
const int in3 = 2;
const int in4 = 5;

bool notRan;
/*================MOVEMENT FUNCTIONS===================*/

void moveForward(int speed);
void moveBackward(int speed);
void halt();
void turnLeft();
void turnRight();

/*================TESTING FUNCTIONS====================*/
void back_and_forth(int speed);
void go_in_loop();
void spinMoveBaby();

void printWifiData();
bool pingTest();


void setup() 
{
  Serial.begin(9600);
  int connectionAttempts = 1;

  // Try to establish a WIFI Connection
  while ( status != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    Serial.print("Attempt #");
    Serial.println(connectionAttempts);
    
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // Wait 10 seconds for connection:
    delay(10000);
    if(status != WL_CONNECTED)
        Serial.print("Connection failed... Attempting Again");
  }
  Serial.println("CONNECTION SUCCESS!");

  // Attempt to ping Google
  while(!pingTest());
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  notRan = true;
}

void loop() 
{
  int speed = 255; // NOTE: range from 0 - 255
  if(notRan)
    
  
  notRan = false;
}

void moveForward(int speed)
{
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward(int speed)
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
  delay(1000);
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
    moveForward(255);
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

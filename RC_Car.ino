// Right Motor
const int enA = 10;
const int in1 = 4;
const int in2 = 3;

// Left Motor
const int enB = 9;
const int in3 = 2;
const int in4 = 5;

bool notRan;

void moveForward(int speed);
void moveBackward(int speed);
void halt();
void turnLeft();
void turnRight();

//TESTING FUNCTIONS
void back_and_forth(int speed);
void go_in_loop();
void spinMoveBaby();

void setup() 
{
  Serial.begin(9600);
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
    spinMoveBaby();
  
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
void turnRight();

/* TESTING FUNCTIONS */
void back_and_forth(int speed)
{

  analogWrite(enA, speed);
  analogWrite(enB, speed);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
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

#include <Servo.h>

char ZChannel=0, YChannel=1;
char serialChar=0;

const int TrigPin = 8;
const int EchoPin = 9;
float cm;

Servo servoZ, servoY;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int Z = 0;    // variable to store the servo position
int Y = 0;

const int Y_START = 160;
const int Y_END = 140;

void PING(){
  delay(250);
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58.0; //The echo time is converted into cm
  cm = (int(cm * 100.0)) / 100.0; //Keep two decimal places
  //String output = Z;
  Serial.print(Z);
  Serial.print("|");
  Serial.print(Y);
  Serial.print("|");
  Serial.print(cm);
  Serial.print('X');
}

void ReturnY()
{
   for (Y = Y_END; Y <= Y_START; Y+= 1) { // goes from 0 degrees to 180 degrees
   servoY.write(Y);              // tell servo to go to position in variable 'pos'
   delay(20);
   }
}

void setup() {
  servoZ.attach(3);  // attaches the servo on pin 9 to the servo object
  servoY.attach(5);

  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  for (Z = 0; Z <= 120; Z += 5) { // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
    servoZ.write(Z);              // tell servo to go to position in variable 'pos'
    for (Y = Y_START; Y >= Y_END; Y-= 1) { // goes from 0 degrees to 180 degrees
      servoY.write(Y);              // tell servo to go to position in variable 'pos'
      if (Y%5==0){
        PING();
      }
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    ReturnY();
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  for (Z = 120; Z >= 0; Z -= 5) { // goes from 0 degrees to 180 degrees
    servoZ.write(Z);
    delay(15);  
  }

  Serial.print("END");
  Serial.print("X");
  servoZ.detach();
  servoY.detach();

}

void loop(){

}

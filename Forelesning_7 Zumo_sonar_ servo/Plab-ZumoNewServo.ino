/*
Tests servo on Zumo using the ServoTimer2 library
*/

#include <NewServo.h>

#define SERVO_PIN 0
NewServo servo;


void setup()
{
  // initialise servo
  servo.attach(SERVO_PIN);
}
 
void loop()
{
  // Turn servo 0, 90 and 180 degrees - and repeat
  servo.write(0);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(180);
  delay(1000);
}

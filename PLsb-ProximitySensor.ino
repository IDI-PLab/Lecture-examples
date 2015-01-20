#include <NewPing.h>
// Library NewPing from:
// https://code.google.com/p/arduino-new-ping/downloads/detail?name=NewPing_v1.5.zip&can=2&q=

const int echoPin = 7;
const int triggerPin = 8;
const int maxDistance = 300;
 
NewPing sonar(triggerPin, echoPin, maxDistance);
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  // Får tiden det tar med et ping
  unsigned int time = sonar.ping();
   
  // Beregn hvor langt dette var
  float distance = sonar.convert_cm(time);
 
  Serial.println(distance);
  delay(50);
}

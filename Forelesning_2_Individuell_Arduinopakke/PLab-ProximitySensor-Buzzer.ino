#include "NewPing.h"
// Library NewPing from:
// https://code.google.com/p/arduino-new-ping/downloads/detail?name=NewPing_v1.5.zip&can=2&q=

const int echoPin = 7;
const int triggerPin = 8;
const int maxDistance = 100;  // default 300 
NewPing sonar(triggerPin, echoPin, maxDistance);

int speakerOut = 9; // Put speaker through 220 ohm on pin 9.
int frequency = 0;
int duration = 200;

void setup() {
   pinMode(speakerOut, OUTPUT);
}

// Function to produce one square pulse of a
// given frequency on a given pin:
void playTone(int pin, int freq, int dur) {
  long int pulseLength = 500000 / freq;
  long int durLong = dur;
  long int noOfPulses = (durLong*1000) / (pulseLength*2);
  for (long int i = 0; i < noOfPulses; i++) {
     digitalWrite(pin, HIGH);
     delayMicroseconds(pulseLength);
     digitalWrite(pin, LOW);
     delayMicroseconds(pulseLength);
  }
}


void loop() {
//   Får tiden det tar med et ping
   unsigned int time = sonar.ping();
//   Beregn hvor langt dette var
   float distance = sonar.convert_cm(time);
 //  if (distance == 0) {
 //   distance = maxDistance;
 //  };
   frequency = 30 * distance;
   playTone(speakerOut, frequency, 200); 
   delay(50);
}

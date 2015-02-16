// Including library to do serial communication with bluetooth
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>
#include <ZumoMotors.h>

const int btUnitTxPin = 2; // Connected to tx on bt unit
const int btUnitRxPin = 6; // Connected to rx on bt unit
PLabBTSerial btSerial(btUnitTxPin, btUnitRxPin);
ZumoMotors motors;

void setup(void)
{ 
  // Start communication with bluetooth unit
  btSerial.begin(9600);
}

void loop()
{
  // See if we have received a new character
  int availableCount = btSerial.available();
  if (availableCount > 0) {
    char text[availableCount];
    btSerial.read(text, availableCount); 
    readCommand(text);
  }
}

void readCommand (char *text) {
  if (0 == strcmp("ON", text)) {
    motors.setSpeeds(100, 100);
  } else if (0 == strcmp("OFF", text)) {
    motors.setSpeeds(0, 0);
  } 
}

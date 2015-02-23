// Including library to do serial communication with bluetooth
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>
#include <ZumoMotors.h>
#include <PLab_ZumoMotors.h>

const int btUnitTxPin = 2; // Connected to tx on bt unit
const int btUnitRxPin = 6; // Connected to rx on bt unit
PLabBTSerial btSerial(btUnitTxPin, btUnitRxPin);
// ZumoMotors motors;
PLab_ZumoMotors PLab_motors;

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
  if (0 == strcmp("FORWARD", text)) {
    PLab_motors.setSpeeds(200, 200);
  } else if (0 == strcmp("STOP", text)) {
    PLab_motors.setSpeeds(0, 0);
  } else if (0 == strcmp("BACKWARD", text)) {
    PLab_motors.setSpeeds(-200, -200);
  } else if (0 == strcmp("LEFT", text)) {
    PLab_motors.turnLeft(200, 90);
  } else if (0 == strcmp("L45", text)) {
   PLab_motors.turnLeft(200, 45);
  } else if (0 == strcmp("RIGHT", text)) {
    PLab_motors.turnRight(200, 90);
  } else if (0 == strcmp("R45", text)) {
   PLab_motors.turnRight(200, 45);  
  } else if (0 == strcmp("STEPF", text)) {
    PLab_motors.forward(200, 5);
  } else if (0 == strcmp("STEPB", text)) {
   PLab_motors.backward(200, 5);  
  } 
}

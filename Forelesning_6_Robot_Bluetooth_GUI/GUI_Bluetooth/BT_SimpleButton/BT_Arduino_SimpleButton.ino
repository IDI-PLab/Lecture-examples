// Including library to do serial communication with bluetooth
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>

const int btUnitTxPin = 2; // Connected to tx on bt unit
const int btUnitRxPin = 3; // Connected to rx on bt unit
PLabBTSerial btSerial(btUnitTxPin, btUnitRxPin);

// Which output we have the lights connected to
const int LIGHT_OUT = 4;

void setup(void)
{ 
  // Start communication through console
  Serial.begin (9600);
  Serial.println ("Enkel knapp demonstrasjon med BLUETOOTH");
  
  // Set the output for our light
  pinMode (LIGHT_OUT, OUTPUT); 
  digitalWrite (LIGHT_OUT, LOW);
  
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
  Serial.print ("Mottok: ");
  Serial.println (text);
  if (0 == strcmp("ON", text)) {
    digitalWrite (LIGHT_OUT, HIGH);
    Serial.println("Lys paa");
  } else if (0 == strcmp("OFF", text)) {
    digitalWrite (LIGHT_OUT, LOW);
    Serial.println("Lys av");
  } else {
    // This should not happen, so we can tell that it did
    Serial.print ("Ukjent kommando!");
  }
}

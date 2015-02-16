// Including library to do serial communication with bluetooth
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>
#include <PLab_PushButton.h>

const int btUnitTxPin = 2; // Connected to tx on bt unit
const int btUnitRxPin = 3; // Connected to rx on bt unit
PLabBTSerial btSerial(btUnitTxPin, btUnitRxPin);


// Which output we have the lights connected to
const int LIGHT_OUT = 4;

const int buttonPin = 5;
PLab_PushButton myButton(buttonPin);

void setup(void) { 
  // Set the input for button
  pinMode (buttonPin, INPUT); 
  
  pinMode (LIGHT_OUT, OUTPUT); 
  digitalWrite (LIGHT_OUT, LOW);
  
  // Start communication with bluetooth unit
  btSerial.begin(9600);
}

void loop() {
  myButton.update();
  if (myButton.pressed()) {
    digitalWrite (LIGHT_OUT, HIGH);
    btSerial.println("ON"); } 
  else  if (myButton.released()) {
    digitalWrite (LIGHT_OUT, LOW);
    btSerial.println("OFF"); } 
}


#include "PLab_PushButton.h"

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int ledState = LOW;          // State of LED.
PLab_PushButton myButton(buttonPin); // Create a PushButton object.

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  myButton.update();  // Update: Read the switch.
  if (myButton.pressed()) {  // Was the button pressed?      
    if (ledState == LOW) {  // Toggle LED.
        ledState = HIGH; }
    else {
        ledState = LOW; };
  };
  digitalWrite(ledPin, ledState);
}

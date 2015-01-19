#include "PushButton.h"

const int redButtonPin = 2;     // the number of the pushbutton pin
const int redLedPin =  3;      // the number of the LED pin
int redLedState = LOW;          // State of LED.
PushButton redButton(redButtonPin); // Create a PushButton object.

const int greenButtonPin = 4;     // the number of the pushbutton pin
const int greenLedPin =  5;      // the number of the LED pin
int greenLedState = LOW;          // State of LED.
PushButton greenButton(greenButtonPin); // Create a PushButton object.

void setup() {
  // initialize the LED pin as an output:
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);  
}

void loop() {
  redButton.update();  // Update: Read the switch.
  greenButton.update();  // Update: Read the switch.
  
  if (redButton.pressed()) {  // Was the button pressed?      
    if (redLedState == LOW) {  // Toggle LED.
        redLedState = HIGH; }
    else {
        redLedState = LOW; };
  };
  digitalWrite(redLedPin, redLedState);
  
  if (greenButton.pressed()) {  // Was the button pressed?      
    if (greenLedState == LOW) {  // Toggle LED.
        greenLedState = HIGH; }
    else {
        greenLedState = LOW; };
  };
  digitalWrite(greenLedPin, greenLedState);   
}

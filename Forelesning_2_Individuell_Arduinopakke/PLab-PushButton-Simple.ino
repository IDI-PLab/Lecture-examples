#include "PushButton.h"

const int buttonPin = 2;     // the number of the pushbutton pin
PushButton myButton(buttonPin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  myButton.update();  // Update: Read the switch.
  if (myButton.pressed()) {  // Was the button pressed?
    Serial.println("Pressed."); 
  };
  if (myButton.released()) {   // Was the button released?
    Serial.println("Released.");
   };
  if (myButton.isDown()) {  // Is the button down?
  //  Serial.print(".");
  };
}

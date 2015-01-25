
// these constants describe the pins. They won't change:

int speakerOut = 6; // Put speaker through 220 ohm on pin 9.
int micInput = 8;
int micValue = 0;
int frequency = 440;
const int RGB_bluepin = 4;

void setup()
{
  pinMode(speakerOut, OUTPUT);
  pinMode(micInput, INPUT);
  pinMode(RGB_bluepin, OUTPUT);   // sets the pin as output 
}

void loop()
{
   micValue = digitalRead(micInput);
   digitalWrite(RGB_bluepin, !micValue); 
   if (!micValue) {
       tone(speakerOut,frequency,50); delay(50);
   }
}


// these constants describe the pins. They won't change:

int speakerOut = 6; // Put speaker through 220 ohm on pin 9.
int touchInput = 5;
int touchValue = 0;
int frequency = 1000;

void setup()
{
  pinMode(speakerOut, OUTPUT);
  pinMode(touchInput, INPUT);
  Serial.begin(9600);
}


// Function to produce one square pulse of a
// given frequency on a given pin:
void playOneSquarePulse(int pin, int freq) {
  long int pulseLength = 500000 / freq;
  digitalWrite(pin, HIGH);
  delayMicroseconds(pulseLength);
  digitalWrite(pin, LOW);
  delayMicroseconds(pulseLength);
}

void loop()
{
   touchValue = digitalRead(touchInput);
   Serial.println(touchValue);
   if (touchValue == HIGH) {
     playOneSquarePulse(speakerOut, frequency);
    
   }
}


// these constants describe the pins. They won't change:

int speakerOut = 6; // Put speaker through 220 ohm on pin 9.
int hallInput = 7;
int hallValue = 0;
int frequency = 1000;
const int RGB_bluepin = 4;
void setup()
{
  pinMode(speakerOut, OUTPUT);
  pinMode(hallInput, INPUT);
  pinMode(RGB_bluepin, OUTPUT);   // sets the pin as output 
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
   hallValue = digitalRead(hallInput);
   Serial.println(hallValue);
   digitalWrite(RGB_bluepin, !hallValue); 
   if (hallValue == LOW) {
     playOneSquarePulse(speakerOut, frequency);
    
   }
}

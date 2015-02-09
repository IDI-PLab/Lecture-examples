//TMP35 Pin Variables
int sensorPin = A3; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures

int speakerOut = 6; // Put speaker through 220 ohm on pin 9.
int micValue = 0;
int frequency = 0;
const int RGB_bluepin = 4;
const int RGB_redpin = 2;

void setup()
{
  pinMode(RGB_redpin, OUTPUT);   // sets the pin as output
  pinMode(RGB_bluepin, OUTPUT);   // sets the pin as output  
  pinMode(speakerOut, OUTPUT);
}
 
// Function to produce one square pulse of a
// given frequency on a given pin:
void playOneSquarePulse(int pin, int freq) {
  long int pulseLength = 500000.0 / freq;
  digitalWrite(pin, HIGH);
  delayMicroseconds(pulseLength);
  digitalWrite(pin, LOW);
  delayMicroseconds(pulseLength);
} 
 
void loop()                     // run over and over again
{
 //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  
 float voltage = reading * 5.0 / 1024.0; 
 float temperatureC = voltage * 100.0 ;  //converting from 10 mv per degree                                            //to degrees ((volatge - 500mV) times 100)
 if (temperatureC > 25.0) {
    digitalWrite(RGB_redpin, HIGH); 
    digitalWrite(RGB_bluepin,LOW);}
 else {
    digitalWrite(RGB_redpin, LOW); 
    digitalWrite(RGB_bluepin,HIGH); 
 };
 frequency = (temperatureC - 20.0) * 100.0;
 if (frequency < 100) {frequency = 100;};
 playOneSquarePulse(speakerOut, frequency);
}

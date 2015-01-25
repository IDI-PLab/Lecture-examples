
// these constants describe the pins. They won't change:
const int RGB_redpin = 2;
const int RGB_greenpin = 3;
const int RGB_bluepin = 4;

void setup()
{
  // initialize the serial communications:
  pinMode(RGB_redpin, OUTPUT);   // sets the pin as output
  pinMode(RGB_greenpin, OUTPUT);   // sets the pin as output
  pinMode(RGB_bluepin, OUTPUT);   // sets the pin as output 
}

void loop()
{
  // print the sensor values:
  for (int r=0; r <= 1; r++) {
    for (int g=0; g <= 1; g++) {
      for (int b=0; b <= 1; b++) {
         analogWrite(RGB_redpin, r*255); 
         analogWrite(RGB_greenpin,g*255); 
         analogWrite(RGB_bluepin,b*255); 
         delay(500);
  }}}
}

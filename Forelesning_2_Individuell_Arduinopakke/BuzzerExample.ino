/*
  Buzzer Example
  
  Dette er et eksempel paa hvordan en enkel buzzer kan brukes til aa spille en liten melodi.
  Fire toner spilles i loop. Advarsel: Maa ikke kjoeres for lenge, fare for mentale skader for omgivelsene.
  
  Kretsen
    - TMB12A05 buzzer
    - 220 ohm motstand


  This is an example to show how a simple buzzer may be used to play a little melody.
  Four tones are played in a loop. Warning: Do not run too long. You may damage the mental health of your surroundings.
  
  Circuit
    - TMB12A05 buzzer
    - 220 ohm resistor
*/

// Pinnen vi spiller paa
// The pin we are playing on
const int soundPin = 8;
// Lengden paa tonen som vi spiller
// Length of the tone we are playing
const int toneLength = 500;

void setup() {
  // Trenger ikke klargjoere noe
  // Do not need to ready anything
}

void loop() {
  // tone gir en frekvens paa pinnen som er gitt. Tallet er frekvensen (440 Hz er kammertonen, A4). Merk, det siste argumentet, tonelengde, er valgfritt.
  // tone gives a frequency on the given pin. The number represents the frequency (440 Hz is equal to A4). Note, the last argument, tone length, is optional.
  tone(soundPin, 440, toneLength);
  // Vi tar en kort pause etter den foerste tonen, derfor er delay to ganger
  // We take a little pause after the first sound, that is why we have two delays
  delay(toneLength);
  delay(toneLength);
  
  tone(soundPin, 1000, toneLength);
  delay(toneLength);
  
  // Ingen pause mellom tonene; det er tatt pause akkurat like lenge som vi spiller tonen
  // No pause between the tones; the delay takes the exact same amount of time as the tone is set to play
  
  tone(soundPin, 2000, toneLength);
  delay(toneLength);
  
  tone(soundPin, 2500, toneLength);
  delay(toneLength);
}

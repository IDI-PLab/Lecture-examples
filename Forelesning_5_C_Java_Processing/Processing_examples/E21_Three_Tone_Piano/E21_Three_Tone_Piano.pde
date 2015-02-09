// My First Square
//

// This program draws a 100x100 square on a 200x200 canvas.
// 

import ddf.minim.*;
import ddf.minim.signals.*;
import ddf.minim.effects.*;

Minim minim;
AudioOutput out;
SineWave mySound;

void setup() {                    // Called once when the program is started.
  size(200, 200);                 // Canvas size is 200 x 200 pixels.
  background(128,128,128);        // Background color is grey (128,128,128).
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
  minim = new Minim(this);
  // get a stereo line out with a sample buffer of 512 samples
  out = minim.getLineOut(Minim.STEREO, 512);
  mySound = new SineWave(1, 1, 44100);
  mySound.setAmp(0.0);
  out.addSignal(mySound);
}

void draw() {                     // Called for every frame (10x per second).
  rect(50,50,100,100);            // Draw a rectangle upper left corner (50,50), size (100x100)
}

void keyReleased() {
  fill(255,255,255);
    mySound.setAmp(0.0);
}

void keyPressed() {
   mySound.setAmp(1.0);
  if (key == 'r') {
    fill(255,0,0); 
    mySound.setFreq(523.251);}   // C5
  else if (key == 'g') {
    fill(0,255,0);
  mySound.setFreq(587.330);}    // D5   
  else if (key == 'b') {
    fill(0,0,255);
    mySound.setFreq(659.255);}   // E5
  else {
    fill(0,0,0);
   mySound.setFreq(1);}
}


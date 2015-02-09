// My First Square
//

// This program draws a 100x100 square on a 200x200 canvas.
// 

import java.awt.event.*;

int y = 50;

void setup() {                    // Called once when the program is started.
  addMouseWheelListener(new MouseWheelListener() { 
    public void mouseWheelMoved(MouseWheelEvent mwe) { 
      mouseWheel(mwe.getWheelRotation());
  }}); 
  size(200, 200);                 // Canvas size is 200 x 200 pixels.
  background(128,128,128);        // Background color is grey (128,128,128).
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
  fill(255,255,255);
}

void draw() {                     // Called for every frame (10x per second).
  background(128,128,128);        // Background color is grey (128,128,128).
  rect(50,50,y,y);            // Draw a rectangle upper left corner (50,50), size (100x100)
}


void mouseWheel(int delta) {
  y = y - delta;
}


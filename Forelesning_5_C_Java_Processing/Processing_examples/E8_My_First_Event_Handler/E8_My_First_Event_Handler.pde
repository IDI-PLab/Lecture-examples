// My First Event Handler

// This program draws a 100x100 square on a 200x200 canvas.
// 

void setup() {                    // Called once when the program is started.
  size(200, 200);                 // Canvas size is 200 x 200 pixels.
  background(0,255,0);        // Background color is grey (128,128,128).
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
  fill(255,0,0);
}

void draw() {                     // Called for every frame 
 // background(128,128,128);
  rect(50,50,100,100);            // Draw a rectangle upper left corner (50,50), size (100x100)
}

void mouseReleased() {
  fill(255,0,0);
  background(0,255,0);
}

void mousePressed() {
  fill(0,255,0);
  background(255,0,0);
}

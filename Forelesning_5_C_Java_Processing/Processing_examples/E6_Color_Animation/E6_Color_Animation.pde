// My First Square
//
// This program draws a 100x100 square on a 200x200 canvas.
// 
int red = 128;
int increment = 1;

void setup() {                    // Called once when the program is started.
  size(200, 200);                 // Canvas size is 200 x 200 pixels.
  background(128,128,128);        // Background color is grey (128,128,128).
}

void draw() {                     // Called for every frame 
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
  fill(red,0,0);              // Fill color is a combination of Red and Green.
  rect(50,50,100,100);            // Draw a rectangle upper left corner (50,50), size (100x100)
  red = red + increment;
  if (red > 255)
    {increment = -1;};
   if (red <= 0)
    {increment = 1;};
}



// My Second Animation
//

// This program draws a 100x100 square on a 200x200 canvas.
// Two squares move from left to right and back.
// 
int x1 = 0;
int increment1 = 6;
int i1 = increment1;
int x2 = 0;
int increment2 = 10;
int i2 = increment2;

void setup() {                    // Called once when the program is started.
  size(400, 400);                 // Canvas size is 200 x 200 pixels.
  frameRate(15);
}

void draw() {                     // Called for every frame
  background(128,128,128);        // Background color is grey (128,128,128).
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
  fill(0,0,255);              // Fill color is white (255,255,255)
  rect(x1,50,100,100);             // Draw a rectangle upper left corner (x,50), size (100x100)
  x1 = x1 + i1;
  if (x1 >= 300) {
    i1 = -increment1;
  };
  if (x1 <= 0) {
    i1 = increment1;
  };
  fill(255,0,0);              // Fill color is white (255,255,255)
  rect(50,x2,100,100);             // Draw a rectangle upper left corner (x,50), size (100x100)
  x2 = x2 + i2;
  if (x2 >= 300) {
    i2 = -increment2;
  };
  if (x2 <= 0) {
    i2 = increment2;
  };
}



// My First Animation

// This program draws a 100x100 icon on a 200x200 canvas.
// The square moves from left to right and back.
// 
int x = 0;
int increment = 1;
int i = increment;
PImage icon;

void setup() {                    // Called once when the program is started.
  size(200, 200);                 // Canvas size is 200 x 200 pixels.
  frameRate(60);
  icon = loadImage("icon.jpg");
}

void draw() {                     // Called for every frame (10x per second).
  background(0);        // Background color is grey (128,128,128).
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
  fill(255,255,255);              // Fill color is white (255,255,255)
//  rect(x,50,100,100);             // Draw a rectangle upper left corner (x,50), size (100x100)
  image(icon,x,50,100,100);
  x = x + i;
  if (x >= 100) {
    i = -increment;
  };
  if (x <= 0) {
    i = increment;
  };
}



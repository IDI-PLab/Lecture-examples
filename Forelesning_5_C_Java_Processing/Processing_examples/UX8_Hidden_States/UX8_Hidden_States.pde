// My First Square
//

// This program draws a 100x100 square on a 200x200 canvas.
// 

int state = 0;
int noOfStates = 4;

void setup() {                    // Called once when the program is started.
  size(200, 200);                 // Canvas size is 200 x 200 pixels.
  background(128);        // Background color is grey (128,128,128).
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
}

void draw() {    // Called for every frame
  switch (state) {
    case 0: fill(0); break;
//    case 1: fill(80); break;
    case 2: fill(190); break;   
//    case 3: fill(255); break;  
  };
  rect(50,50,100,100);            // Draw a rectangle upper left corner (50,50), size (100x100)
}

void mousePressed() {
  if (inside(mouseX, mouseY,50,50,100,100)) {
      if (state < (noOfStates - 1)) {
        state++;} 
      else {
        state = 0;}
  }
}


boolean inside(int x,int y, int x0,int y0,int w,int h) {
  return (((x >= x0) && (x < (x0+w))) && 
      ((y >= y0) && (y < (y0+h))));
}

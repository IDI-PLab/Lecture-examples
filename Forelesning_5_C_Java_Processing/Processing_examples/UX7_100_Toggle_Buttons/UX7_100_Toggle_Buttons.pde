// My First Square
//
// This program draws a 100x100 square on a 200x200 canvas.
// 

boolean toggleOn[][] = new boolean[10][10];

void setup() {                    // Called once when the program is started.
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      toggleOn[i][j] = false;
    }
  };
  size(300, 300);                 // Canvas size is 200 x 200 pixels.
  background(128);                // Background color is grey (128,128,128).
  stroke(67);                     // Stroke color is dark grey.
}

void draw() {                                     // Called for every frame
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      if (toggleOn[i][j]) {
        fill(255);
      } 
      else {
        fill(0,i,j);
      };
      rect(50+i*20, 50+j*20, 20, 20);
    }
  }
}

void mousePressed() {
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      if (inside(mouseX, mouseY, 50+i*20, 50+j*20, 20, 20)) {
        toggleOn[i][j] = !toggleOn[i][j];
      }
    }
  }
}


boolean inside(int x, int y, int x0, int y0, int w, int h) {
  return (((x >= x0) && (x < (x0+w))) && 
    ((y >= y0) && (y < (y0+h))));
}


// My First Square
//

// This program draws a 100x100 square on a 200x200 canvas.
// 

int distance = 50;

PImage offImage, onImage, drawImage;

void setup() {                    // Called once when the program is started.
  size(300, 400);                 // Canvas size is 200 x 200 pixels.
  background(0,0,0);        // Background color is grey (128,128,128).
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
  offImage = loadImage("BulbOff.jpg");
  onImage = loadImage("BulbOn.jpg");
  drawImage = offImage;
}

void draw() {                     // Called for every frame (10x per second).
   image(drawImage,50,50,200,300);
}

void mouseReleased() {
    drawImage = offImage;
}

void mousePressed() {
    if (inside(mouseX, mouseY,150-distance,150-distance,2*distance,2*distance)) {
        drawImage = onImage;} 
}

boolean inside(int x,int y, int x0,int y0,int w,int h) {
  return (((x >= x0) && (x < (x0+w))) && 
      ((y >= y0) && (y < (y0+h))));
}

// My First Square
//

// This program draws a 100x100 square on a 200x200 canvas.
// 

int distanceA = 50;
int distanceB = 100;

PImage offImage, onImage, drawImageA, drawImageB;

void setup() {                    // Called once when the program is started.
  size(350, 250);                 // Canvas size is 200 x 200 pixels.
  background(0,0,0);        // Background color is grey (128,128,128).
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
  offImage = loadImage("BulbOff.jpg");
  onImage = loadImage("BulbOn.jpg");
  drawImageA = offImage;
  drawImageB = offImage;  
}

void draw() {                     // Called for every frame (10x per second).
   image(drawImageA,50,50,100,150);
   image(drawImageB,200,50,100,150);   
}

void mouseReleased() {
    drawImageA = offImage;
    drawImageB = offImage;
}

void mousePressed() {
    if (inside(mouseX, mouseY,100-distanceA,125-distanceA,2*distanceA,2*distanceA)) {
        drawImageA = onImage;} 
    if (inside(mouseX, mouseY,250-distanceB,125-distanceB,2*distanceB,2*distanceB)) {
        drawImageB = onImage;} 
}

boolean inside(int x,int y, int x0,int y0,int w,int h) {
  return (((x >= x0) && (x < (x0+w))) && 
      ((y >= y0) && (y < (y0+h))));
}

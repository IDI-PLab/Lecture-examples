// My First Square

// This program draws a 100x100 square on a 200x200 canvas.
// 

int x = 50;
int y = 50;
int previousMouseX, previousMouseY;

void setup() {                    // Called once when the program is started.
  size(500, 400);                 // Canvas size is 200 x 200 pixels.
  stroke(0);                  // Stroke color is black (0,0,0)
  fill(255);
  frameRate(120);
}

void draw() {                     // Called for every frame.
  background(128);        // Background color is grey (128,128,128).
  fill(255);
  stroke(0);
  rect(x,y,100,100);            // Draw a rectangle upper left corner (50,50), size (100x100)
  fill(128);
  stroke(128);
  rect(200,50,100,100);
  rect(200,200,100,100);
  textSize(32);
  text("Secret",320,110);
  text("text",320,260);
  
}

void mousePressed() {
  previousMouseX = mouseX;
  previousMouseY = mouseY;  
}

void mouseDragged() {
  if (inside(previousMouseX, previousMouseY,x,y,100,100)) {
       x = x + mouseX - previousMouseX;
       y = y + mouseY - previousMouseY;   
       previousMouseX = mouseX;
       previousMouseY = mouseY;  
    } 

}

boolean inside(int x,int y, int x0,int y0,int w,int h) {
  return (((x >= x0) && (x < (x0+w))) && 
      ((y >= y0) && (y < (y0+h))));
}

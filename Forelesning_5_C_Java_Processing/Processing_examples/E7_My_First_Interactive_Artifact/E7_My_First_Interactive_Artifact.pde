// My First interactive artefact
//
// 

void setup() {                    // Called once when the program is started.
  size(200, 200);                 // Canvas size is 200 x 200 pixels.
  background(128,128,128);        // Background color is grey (128,128,128).
}

void draw() {                     // Called for every frame
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
  if (mousePressed == true) {
    fill(0,0,0);
  } else {
    fill(255,255,255);
  }
  rect(50,50,100,100);            // Draw a rectangle upper left corner (50,50), size (100x100)
}



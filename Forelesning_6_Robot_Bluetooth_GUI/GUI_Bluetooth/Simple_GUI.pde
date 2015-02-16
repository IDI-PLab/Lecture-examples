//
//  Minimal Processing GUI library.
//  PLab 2015
//
//  Dag Svanæs, IDI, NTNU.
// 

int[] white = {255,255,255};
int[] black = {0,0,0};
int[] red = {255,0,0};
int[] green = {0,255,0};
int[] blue = {0,0,255};
int[] yellow = {255,255,0};
int[] gray = {128,128,128};

boolean inside(int x,int y, int x0,int y0,int w,int h) {
  return (((x >= x0) && (x < (x0+w))) && 
      ((y >= y0) && (y < (y0+h))));
}

boolean mouseInside(int[] rect) {
  return inside(mouseX, mouseY, rect[0],rect[1],rect[2],rect[3]);
}

void drawButton(int[] xywh, String buttonText) {
    boolean mousePressedInButton = mouseInside(xywh) && mousePressed;
    stroke(0);
    if (mousePressedInButton) {
      fill(0); }
    else {
      fill(255); 
    } 
    rect(xywh[0],xywh[1],xywh[2],xywh[3],10);
    if (mousePressedInButton) {
      fill(255); }
    else {
      fill(0); 
    }   
    int tSize = xywh[3] * 3 / 5;
    textSize(tSize);
    textAlign(CENTER, CENTER);
    text(buttonText,xywh[0]+xywh[2]/2,xywh[1]+xywh[3]/2-2);
}

void drawText(int[] xywh, String buttonText) {
    stroke(0);
    fill(255);  
    rect(xywh[0],xywh[1],xywh[2],xywh[3]);
    fill(0);  
    int tSize = xywh[3] * 3 / 5;
    textSize(tSize);
    textAlign(LEFT, CENTER);
    text(buttonText,xywh[0]+2,xywh[1]+xywh[3]/2-2);
}
  
void drawRectangle(int[] xywh, int[] drawColor) {
    stroke(0);
    fill(drawColor[0],drawColor[1],drawColor[2]);  
    rect(xywh[0],xywh[1],xywh[2],xywh[3]);
}

void drawCircle(int[] xyr, int[] drawColor) {
    stroke(0);
    fill(drawColor[0],drawColor[1],drawColor[2]);  
    ellipseMode(RADIUS);
    ellipse(xyr[0],xyr[1],xyr[2],xyr[2]);
}


//---------------------------------

int[] buttonFrame1 = {10,10,100,25};
String buttonString1 = "Hei";

int[] buttonFrame2 = {10,50,100,25};
String buttonString2 = "Hallo";

int[] textFrame1 = {10,100,150,50};
String textString1 = "...";

int[] rectFrame1 = {20,160,20,20};
int[] rectColor1 = white;  

int[] circleXYR1 = {60,170,10};  // Circle in <50,170> with radius 10.
int[] circleColor1 = white;  
 
void setup() {
  size(300,200);              // Canvas size is 200 x 200 pixels.
  background(128);            // Background color is gray (128,128,128).
  stroke(0);                  // Stroke color is black (0,0,0)
}

void draw() {    // Called for every frame
  drawButton(buttonFrame1,buttonString1);
  drawButton(buttonFrame2,buttonString2);
  drawText(textFrame1,textString1);
  drawRectangle(rectFrame1,rectColor1);
  drawCircle(circleXYR1,circleColor1);
}

void mousePressed() {
   if (mouseInside(buttonFrame1)) {
     textString1 = "Hei";
     rectColor1 = red;  // Red..
     circleColor1 = blue;
   } else 
   if (mouseInside(buttonFrame2)) {
     textString1 = "Hallo"; 
     rectColor1 = green;  // 
     circleColor1 = yellow;    
   }   
}

void mouseReleased() {
}




// DS - Graphics element library
//


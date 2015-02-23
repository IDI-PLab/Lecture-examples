/*
* ---------- Interfaces that make conversion to mobile simpler ----------
*/
// Interfaces documented in InterfacesExample
interface PLabBridge {
  public int getWidth ();
  public int getHeight ();
  public void write (String string);
  public void subscribeRead (PLabRead sub);
  public void subscribeError (PLabRead sub);
  public void disconnect();
}
interface PLabRead {
  public void read(String string);
}


/*
 * ---------- Binding the code with call javascript/serial port ----------
 */
private PLabBridge pBridge;
private String received = null;

void bindPLabBridge (PLabBridge bridge) {
  size(bridge.getWidth(), bridge.getHeight());
  pBridge = bridge;
  
  // Subscribe to messages. Print incomming messages and change color of drawing
  bridge.subscribeRead(new PLabRead() {
    public void read (String string) {
     //  btRead(string.substring(0,string.length()-2));
    }
  });
}

void btWrite(String string) {
  if (pBridge != null) {
    pBridge.write(string);
  }
}

/* 
  This is an implementation of the game Blind Rabbit for Arduino.
  The user interface of Blind Rabbit consist of a 3x3 matrix of nine squares
  and four buttons (left, right, up, down).

   The blind rabbit constantly jumps forward on the board
  in the direction it is heading. The purpose of the game is to prevent the rabbit from
  jumping outside the board and die by controlling its direction with the pushbuttons.
  
   . . .          ^
   . . .        <   >
   * . .          v
  
  The rabbit moves at an initial speed of one move per second. If you manage to 
  keep it alive for 10 moves, you will go to the next level of the game where the speed
  will be 25% higher. If it jumps outside and dies, the speed will be the same and you
  have an infinite number of trials at that level.
  
  The challenge is to see how high speed you can manage.

  PLab 2015, Dag Svanæs, IDI, NTNU.
  
*/
//-------------
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

float scaleOfGUI = 1.0;
int canvasWidth = 0, canvasHeight = 0;

void setCanvas(int w, int h) {
  canvasWidth = w;
  canvasHeight = h;
  size(w,h);
}

void scaleGUI() {
   if (pBridge != null) {
     scaleOfGUI = pBridge.getWidth() / canvasWidth;
     scale(scaleOfGUI);
   };
}

boolean inside(int x,int y, int x0,int y0,int w,int h) {
  return (((x >= x0) && (x < (x0+w))) && 
      ((y >= y0) && (y < (y0+h))));
}

boolean mouseInside(int[] rect) {
  int mouseXScaled = int(mouseX / scaleOfGUI);
  int mouseYScaled = int(mouseY / scaleOfGUI);
  return inside(mouseXScaled, mouseYScaled, rect[0],rect[1],rect[2],rect[3]);
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



//-------------------------------------------------

int[] buttonFrame1 = {10,10,100,25};
String buttonString1 = "On";

int[] buttonFrame2 = {10,50,100,25};
String buttonString2 = "Off";

void setup() {
  setCanvas(300,200);              // Canvas size is 200 x 200 pixels.
  background(128);            // Background color is gray (128,128,128).
  stroke(0);                  // Stroke color is black (0,0,0)
}

void btRead(String string) {
  println("Received: " + string);
}
  
void draw() {
  scaleGUI();
  drawButton(buttonFrame1,buttonString1);
  drawButton(buttonFrame2,buttonString2);
}

void mousePressed() {
   if (mouseInside(buttonFrame1)) {
      btWrite("ON");
   } else 
   if (mouseInside(buttonFrame2)) {
      btWrite("OFF");  
   }   
}


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
 * ---------- Bluetooth Serial communication for computer  ---------------------
 */
import processing.serial.*;

class BridgeReplacer implements PLabBridge {
  Serial port;
  PLabRead subscribedRead = null;
  
  BridgeReplacer(Serial serialPort) {
    port = serialPort;
    port.clear();
    
    // Send a message to show we are connected
  //  port.write("Hello world!\n");
    // Buffer data until a newline character is reached
    port.bufferUntil('\n');
  } 
  public int getWidth () {
    return width;
  }
  public int getHeight () {
    return height;
  }
  public void write (String string) {
    port.write(string + "\n");
  }
  public void subscribeRead (PLabRead sub) {
    subscribedRead = sub;
  }
  public void subscribeError (PLabRead sub) { /* We do not care about this while developing */ }
  public void disconnect() { /* We do not care about this while developing */ }
}

BridgeReplacer bridgeReplacer;

void setupSerialPC(String portName) {
  // Display all installed serial ports on computer
  println(Serial.list());
  // Init a new serial connection
  Serial port = new Serial(this, portName, 9600);
  // Set up our replacement for the plab bridge
  bridgeReplacer = new BridgeReplacer(port);
  // "bind" the replacer instead of the javascript used in mobile devices (replace javascript injection)
  bindPLabBridge(bridgeReplacer);
}

boolean setupSerialMac() {
  String[] searchPatterns = {"tty.PLab", "tty.HC"};
  String portName = "";
  for (String s : Serial.list()) {
    for (String p : searchPatterns) {
       if (s.indexOf(p) != -1) {
         portName = s;
       }
    }
  };
  if (portName != "") {
     println(portName);
     Serial port = new Serial(this, portName, 9600);
      //  Set up our replacement for the plab bridge
     bridgeReplacer = new BridgeReplacer(port);
     // "bind" the replacer instead of the javascript used in mobile devices (replace javascript injection)
     bindPLabBridge(bridgeReplacer);
     return true; } 
   else {
     return false;  
  }
  
}

// Event handler when something happens to the serial port
void serialEvent(Serial p) {
  // Ensure the was event was fired from the correct port
  if (p == bridgeReplacer.port) {
    // Try to read until a newline is found
    String msg = p.readString();
    // Check the event was fired because a newline was received, and that we have a receiver
    if (msg != null && bridgeReplacer.subscribedRead != null) {
      // Send message to the one listening
      bridgeReplacer.subscribedRead.read(msg);
    }
  }
}

/*
 * ---------- Binding the code with call javascript/serial port ----------
 */
private PLabBridge pBridge;
private String received = null;

void bindPLabBridge (PLabBridge bridge) {
  pBridge = bridge;
  
  // Subscribe to messages. Print incomming messages and change color of drawing
  bridge.subscribeRead(new PLabRead() {
    public void read (String string) {
       btRead(string);
    }
  });
}

void btWrite(String string) {
  if (pBridge != null) {
    pBridge.write(string);
  }
}
/*
* ---------- End of library  -------------
*/
//------------------------------------------------------------------------------------- 

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

//-------------------------------------------------

int[] buttonFrame1 = {10,10,100,25};
String buttonString1 = "On";

int[] buttonFrame2 = {10,50,100,25};
String buttonString2 = "Off";

boolean bluetoothActive = false;

void setup() {
  size(300,200);              // Canvas size is 200 x 200 pixels.
  background(128);            // Background color is gray (128,128,128).
  stroke(0);                  // Stroke color is black (0,0,0)
  boolean bluetoothActive = setupSerialMac();
}

void btRead(String string) {
  println("Received: " + string);
}
  
void draw() {
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


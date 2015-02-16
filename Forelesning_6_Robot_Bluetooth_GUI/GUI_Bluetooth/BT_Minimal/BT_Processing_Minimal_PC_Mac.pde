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

 
boolean bluetoothActive = false;

void setup() {
  size(100,100);
  boolean bluetoothActive = setupSerialMac();
}

void btRead(String string) {
  println("Received: " + string);
}
  
void draw() {

  background(0);
  stroke(255);
}

void mouseClicked() {
  // Send a message to bt unit
   btWrite("Hello");
   println("Sent: Hello");
}


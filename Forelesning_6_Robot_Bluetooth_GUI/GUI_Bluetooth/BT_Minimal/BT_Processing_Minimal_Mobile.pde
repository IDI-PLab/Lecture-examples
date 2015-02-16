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
 * ---------- End of library ----------
 */
//----------------------------------------------------------------------------------
void setup() {
  // Setup a size for the sketch
  if (pBridge != null) {
     size(pBridge.getWidth (), pBridge.getHeight ()); }
  else {
     size(100,100);
  }
}

void draw() {
  background(0);
  stroke(255);
}

void btRead(String string) {
  println("Received: " + string);
}

void mouseClicked() {
  // Send a message to bt unit
   btWrite("Hello");
   println("Sent: Hello");
}

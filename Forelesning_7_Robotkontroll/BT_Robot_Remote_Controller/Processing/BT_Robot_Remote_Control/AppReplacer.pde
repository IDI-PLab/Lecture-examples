/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * ---------- Serial communication for computer code ---------------------
 * The following code is used to replace the PLab app. The computer you are
 * sitting on must have paired with a Bluetooth device for this to work.
 * INDIVIDUAL CHANGES NECCESARY FOR EACH COMPUTER IS LOCATED IN setupSerial METHOD.
 */
import processing.serial.*;

class BridgeReplacer implements PLabBridge {
  Serial port;
  PLabRecv subscribedMessages = null;
  
  BridgeReplacer(Serial serialPort) {
    port = serialPort;
    port.clear();
    
    // Buffer data until a newline character is reached
    port.bufferUntil('\n');
  } 
  public int getWidth () {
    return width;
  }
  public int getHeight () {
    return height;
  }
  public void send (String string) {
    port.write(string + "\n");
    println("Sent: " + string);
  }
  public void subscribeMessages (PLabRecv sub) {
    subscribedMessages = sub;
  }
  /* Methods that are of little or no meaning while we develop */
  public void disconnect() {}
  public void hideBackButton() {}
  public void showBackButton() {}
  public void vibrate(int milliseconds) {}
  public void addDeviceOrientationListener(PLabOrientationListener listener) {}
  public void removeDeviceOrientationListener(PLabOrientationListener listener) {}
  public void addDeviceAccelerationListener(PLabAccelerationListener listener) {}
  public void removeDeviceAccelerationListener(PLabAccelerationListener listener) {}
  public void setDeviceAccelerationUpdateInterval(int milliseconds) {}
}

BridgeReplacer bridgeReplacer;

void setupSerial() {
  // Get and display all installed serial ports on computer
  String[] serials = Serial.list();
  println(serials);
  // We need to connect to a port.
  
  
  // ---------------------- THIS CODE IS INDIVIDUAL TO EACH COMPUTER!!! ----------------
  // On Windows computer, which one can be seen by name of the port and setting of paired device.
  // On a Mac/unix system, it should be the one containing the name of the device preceeded by tty
  String portName = "";
  
  // The com port here is found since I know which one in the list is the paired device, and I am on a Windows computer

  // ----- Basic search algorithm. Works for Mac
  for (int i = 0; i < serials.length; i++) {
    portName = serials[i];
    // The name of the handed out bt devices contains the phrase "PLab". The first element containing this phrase should be the correct port.
    if (portName != null && portName.contains("PLab")) {
      break;
    }
  }
  
   // portName = "COM12";   For PC uncomment this 
   
  // Init a new serial connection
  Serial port = new Serial(this, portName, 9600);
  // Set up our replacement for the plab bridge
  bridgeReplacer = new BridgeReplacer(port);
  // "bind" the replacer instead of the javascript used in mobile devices (replace javascript injection)
  bindPLabBridge(bridgeReplacer);
}

// Event handler when something happens to the serial port
void serialEvent(Serial p) {
  // Ensure the was event was fired from the correct port
  if (p == bridgeReplacer.port) {
    // Try to read until a newline is found
    String msg = p.readStringUntil('\n');
    // Check the event was fired because a newline was received, and that we have a receiver
    if (msg != null && bridgeReplacer.subscribedMessages != null) {
      // Send message to the one listening
      bridgeReplacer.subscribedMessages.receive(msg);
    }
  }
}
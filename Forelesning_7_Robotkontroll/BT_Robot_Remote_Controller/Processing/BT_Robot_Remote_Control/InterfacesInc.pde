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
 * This file, IntefacesInc.pde, serves as documentation for
 * the interfaces that are used to get extended functionality
 * from the PLab app. The content of this file is inluded in
 * every sketch loaded with the app, and should therefore
 * NOT IN ANY WAY BE INCLUDED as additional source code when
 * loading a sketch. It is encouraged to include it in a project
 * while developing locally, but to ignore it when loading the
 * project from the app.
 */

/**
 * PLabOrientationEvent is the event object received when phone changes orientation
 */
class PLabOrientationEvent {
  /**
   * alpha - magnetic direction (in degrees)
   */
  float alpha;
  /**
   * beta - tilt front-to-back, front is positive (in degrees)
   */
  float beta;
  /**
   * gamma - tilt left-to-right, right is positive(in degrees)
   */
  float gamma;
}
/**
 * PLabAccelerationEvent is the event object received at regular intervals, telling what acceleration is
 */
class PLabAccelerationEvent {
  /**
   * x - acceleration in x direction
   */
  float x;
  /**
   * y - acceleration in y direction
   */
  float y;
  /**
   * z - acceleration in z direction
   */
  float z;
  /**
   * timestamp - when the acceleration was meassured
   */
  float timestamp;
}
/**
 * PLabBridge is the interface we have for communicating with the plab app.
 */
interface PLabBridge {
  /**
   * gets the width we have available to draw on
   */
  public int getWidth ();
  /**
   * gets the height we have available to draw on
   */
  public int getHeight ();
  /**
   * sends a string to a connected bluetooth device. Can not send more than 20 characters.
   */
  public void send (String string);
  /**
   * register callback function that will get the data sent from the connected device
   */
  public void subscribeMessages (PLabRecv sub);
  /**
   * Disconnects the device and returns to main menu
   */
  public void disconnect();
  /**
   * hides the back button
   */
  public void hideBackButton();
  /**
   * display the back button
   */
  public void showBackButton();
  
  /**
   * make the device vibrate for given amount of time. On iOS time will be ignored.
   */
  public void vibrate(int milliseconds);
  /**
   * Listen for device orientation changes
   */
  public void addDeviceOrientationListener(PLabOrientationListener listener);
  /**
   * remove device orientation changes listener
   */
  public void removeDeviceOrientationListener(PLabOrientationListener listener);
  /**
   * Listen for device acceleration changes
   */
  public void addDeviceAccelerationListener(PLabAccelerationListener listener);
  /**
   * remove device acceleration changes listener
   */
  public void removeDeviceAccelerationListener(PLabAccelerationListener listener);
  /**
   * Set milliseconds between each acceleration update
   */
  public void setDeviceAccelerationUpdateInterval(int milliseconds);
}

/**
 * A simple interface that defines the callback read function
 */
interface PLabRecv {
  /**
   * The callback function. Will be called when the connected device sends something to this program.
   */
  public void receive(String message);
}

/**
 * PLabOrientationListener is the interface describing an orientation change listener
 */
interface PLabOrientationListener {
  public void deviceOrientation(PLabOrientationEvent event);
}

/**
 * PLabAccelerationListener is the interface describing an acceleration event listener
 */
interface PLabAccelerationListener {
  public void deviceAcceleration(PLabAccelerationEvent event);
}

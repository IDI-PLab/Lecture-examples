// My First Square
//

// This program draws a 100x100 square on a 200x200 canvas.
// 

int myMouseDelay = 1000;    // //  Milliseconds delay..

PImage offImage, onImage, drawImage;

void setup() {                    // Called once when the program is started.
  size(300, 400);                 // Canvas size is 200 x 200 pixels.
  background(128,128,128);        // Background color is grey (128,128,128).
  stroke(0,0,0);                  // Stroke color is black (0,0,0)
  offImage = loadImage("BulbOff.jpg");
  onImage = loadImage("BulbOn.jpg");
  drawImage = offImage;
}

void draw() {                     // Called for every frame 
   image(drawImage,50,50,200,300);
   executeDelayActions();
}

void mouseReleased() {
    delayedAction(new Delay(myMouseDelay) {
      public void action() {
       drawImage = offImage;}
    });
}

void mousePressed() {
    delayedAction(new Delay(myMouseDelay) {
      public void action() {
       drawImage = onImage;}
    });
}





// Delay library...
import java.util.List;
import java.util.ArrayList;

List<Delay> delays = new ArrayList<Delay>();

void delayedAction(Delay delayObject) {
  delays.add(delayObject);
}

void executeDelayActions() {
  Delay toBeRemoved = null;
  for (Delay delay : delays) {
    if (millis() >= delay.getTargettime()) {
      delay.action();
      toBeRemoved = delay;
    }
  };
  if (toBeRemoved != null) {
    delays.remove(toBeRemoved);
  }
}

public abstract class Delay {
   int targetTime;
   
   public Delay(int millisDelay) {
     targetTime = millis() + millisDelay;
   }
   
   public int getTargettime() {
     return targetTime;}
     
   public abstract void action();
}




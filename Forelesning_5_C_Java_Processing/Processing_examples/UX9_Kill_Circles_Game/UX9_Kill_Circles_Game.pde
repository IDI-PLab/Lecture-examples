// My First Game
//
// 

int maxX = 500;
int maxY = 400;
int minRadius = 50;
int maxRadius = 100;
float speed = 0.25;
float acceleration = 0.02;
int timeBetweenCircle = 5;
int maxTime = 20;

int targetRadius, centerX, centerY;
float radius;
boolean animationRunning = false;
int timeUntilNextCircle = 0;
int r, g, b;
int framerate = 100;
int framesLeft = maxTime*framerate+1;
int timeLeft;
int points = 0;

void setup() {                    // Called once when the program is started.
  size(maxX, maxY);                 // Canvas size .
  frameRate(framerate);
  background(128, 128, 128);        // Background color is grey (128,128,128).
  stroke(0, 0, 0);                  // Stroke color is black (0,0,0)
}

void draw() {                     // Called for every frame 
  framesLeft--;
  timeLeft = framesLeft / framerate;
  if (timeLeft > 0) {   
    if (animationRunning) {
      radius = radius + speed;
      if (radius <= targetRadius) {
        stroke(r, g, b);
        fill(r, g, b);
        ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
        ellipse(centerX, centerY, int(radius), int(radius));
      } 
      else {
        animationRunning = false;
        timeUntilNextCircle = timeBetweenCircle;
      }
    } 
    else {
      timeUntilNextCircle--;
      if (timeUntilNextCircle <= 0) {
        centerX = int(random(maxX));
        centerY = int(random(maxY)); 
        targetRadius = int(random(minRadius, maxRadius));  
        r = int(random(0, 256));
        g = int(random(0, 256));
        b = int(random(0, 256));
        radius = 0.0;
        animationRunning = true;  
        stroke(255);
        noFill();
        ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
        ellipse(centerX, centerY, targetRadius, targetRadius);
      }
    }

  } 
  else {
    noLoop();
  };
  stroke(0); 
  fill(255); 
  rect(8, 10, 120, 45);
  fill(0); 
  textSize(15);
  text("Time left: "+timeLeft, 12, 30);
  text("Points: "+points, 12, 45);
}

void mousePressed() {
  if (mouseInsideCircle(centerX, centerY, targetRadius)) {
    animationRunning = false;
    timeUntilNextCircle = timeBetweenCircle;
    stroke(128);
    fill(128);
    ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
    ellipse(centerX, centerY, targetRadius+2, targetRadius+2); 
    speed = speed + acceleration;  
    points++;
  }
}

boolean mouseInsideCircle(int cX, int cY, int radius) {
  float distance = sqrt(sq(mouseX-cX)+sq(mouseY-cY));   
  return (distance <= radius);
}



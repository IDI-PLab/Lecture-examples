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

int level = 0;
        
boolean[][] ledStatus =     // Status of the 3x3 LED matrix. (false/true).     
      {{false,false,false},
       {false,false,false},
       {false,false,false}};
       
int[] levelRect = {50,360,30,30};
       
int[][][] rectangles = 
     { {{50,50,100,100}, {150,50,100,100}, {250,50,100,100}},
       {{50,150,100,100}, {150,150,100,100}, {250,150,100,100}},
        {{50,250,100,100}, {150,250,100,100}, {250,250,100,100}}};
        
int[][] buttons = 
    { {150,400,100,50}, {150,600,100,50}, {50,500,100,50}, {250,500,100,50}};
    
String[] buttonTexts = {"Up", "Down", "Left", "Right"};

int[] rabbitUpperLeft = {100,100,30};
int[] rabbit = {100,100,30};
        
int rabbitX = 0;  // X-position of the rabbit on the board.
int rabbitY = 0;  // Y-position of the rabbit on the board.
int rabbitDx;     // Direction of rabbit along x-axis  (dx = -1, 0 or 1)
int rabbitDy;     // Direction of rabbit along y-axis  (dy = -1, 0 or 1)

long timeOfLastMove = 0;  // What time was it when the rabbit last moved.
long currentTime = 0;     // The current time from the function millis().
int timeBetweenMoves = 1000;       // Start with 1 second between moves (jumps).
int numberOfMoves = 0;                 // Counter for no of moves made.

 int rows = 3, columns = 3;
 int movesToWin = 10;         // No of moves to win at a level is set to 10.

// restartGame is called initially and each time a level has been played,
// either by dying or by winning and going on to the next level.
void restartGame() {
  ledStatus[rabbitX][rabbitY] = false;  // Reset last position.
  rabbitX = 0;                        // Start in falseer left corner (0,0).
  rabbitY = 0;
  ledStatus[0][0] = true;   // Set LED for start positition to be true (on).
  rabbitDx = 1;  // Start direction = right: (dx = 1, dy = 0)
  rabbitDy = 0;
  numberOfMoves = 0;                // There have been no moves.
}


// Move the rabbit in the direction given by rabbitDx and rabbitDy.
// No LED update, only internally on the table ledStatus.
void moveRabbitTo(int newX, int newY) {   
   ledStatus[rabbitX][rabbitY] = false;  // Turn off LED for current position (X,Y).
   rabbitX = newX;
   rabbitY = newY;
   ledStatus[rabbitX][rabbitY] = true;  // Turn on LED for new position (X,Y).   
}

// Set alle LED pins to a value (true or false)
void setAllLEDsTo(boolean value) {
   for (int x=0; x<3; x++) {           // X = 0..2
     for (int y=0; y<3; y++) {         //   Y = 0..2
        if (value) {
            drawRectangle(rectangles[x][y], red); }
        else {
            drawRectangle(rectangles[x][y], white); }
     }
   }
}

// Blink LEDs to indicate failure at this level.
void doDie() {
  delay(1000);
}   
  
// Fill the LED matrix to indicate success at this level. 
void doWin() {
  delay(1000);
  level++;
  levelRect[2] = levelRect[2] + 30;
} 



boolean isValidPosition(int x, int y) {
    return (x >= 0) && (x < columns) && (y >= 0) && (y < rows);
}

void tick() {  // Called when there is time to move
  int nextRabbitX = rabbitX + rabbitDx; 
  int nextRabbitY = rabbitY + rabbitDy;
  if (isValidPosition(nextRabbitX, nextRabbitY)) {   // If it will end up inside the board
    moveRabbitTo(nextRabbitX, nextRabbitY);
    numberOfMoves++;                  // Count this as a move.
    if (numberOfMoves > movesToWin) {    // If enough moves have been done (10):
      doWin();                        // Indicate success
      timeBetweenMoves = timeBetweenMoves * 3 / 4; // New level with 25% less delay.
      restartGame();                  // Restart
     }
   } else {                   // Else: the rabbit will still be on the board
      doDie();                              // Blink all LEDs to indicate failure.
      restartGame();                        // Restart at same speed (level).
   };
}

// setup is called once.
void setup() {
  restartGame();                      // Restart the game.
  timeOfLastMove = millis();          // Start timing
  size(400,700);   // Canvas size is 400 x 700 pixels.
  background(128); // Background color is gray (128,128,128).
  stroke(0);       // Stroke color is black (0,0,0)
}

void drawGUI() {
   for (int x=0; x<3; x++) {           // X = 0..2
     for (int y=0; y<3; y++) {         //   Y = 0..2
        drawRectangle(rectangles[x][y], white);
     }
   };
   for (int i=0; i<4; i++) {           // X = 0..2
       drawButton(buttons[i],buttonTexts[i]);
   };
   rabbit[0] = rabbitUpperLeft[0] + rabbitX*100;
   rabbit[1] = rabbitUpperLeft[1] + rabbitY*100;   
   drawCircle(rabbit, red);
   drawRectangle(levelRect, green);
}


// The loop is called again and again.
void draw() {
  drawGUI();
  currentTime = millis();   // What is the current time?
  if ((currentTime - timeOfLastMove) > timeBetweenMoves) { // If time for next move 
    tick();                       // Make one move
    timeOfLastMove = millis();    // Reset the timer.
  }
}

void mousePressed() {
  if (mouseInside(buttons[2])) {          // Left button pressed -> (dx,dy) = (-1,0)
    rabbitDx = -1;
    rabbitDy = 0;  
  } else if (mouseInside(buttons[3])) {  // Right button pressed -> (dx,dy) = (1,0)
    rabbitDx = 1;
    rabbitDy = 0;  
  } else if (mouseInside(buttons[0])) {     // Up button pressed -> (dx,dy) = (0,1)
    rabbitDx = 0;
    rabbitDy = -1;  
  } else if (mouseInside(buttons[1])) {   // Down button pressed -> (dx,dy) = (0,-1)
    rabbitDx = 0;
    rabbitDy = 1;  
  }; 
}


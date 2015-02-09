/* 
  This is an implementation of the game Blind Rabbit for Arduino.
  The user interface of Blind Rabbit consist of a 3x3 matrix of nine red LEDs
  and four pushbuttons (left, right, up, down).

  Only one of the nine LEDs in the 3x3 matrix is on at any time, showing the
  position of the blind rabbit. The blind rabbit constantly jumps forward on the board
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
  

#include <PLab_PushButton.h>

int buttonPins[] = {1,2,3,4};   // Arduino pins for buttons Left, Right, Up, Down.

PLab_PushButton leftButton(buttonPins[0]); // Push button object for Left.
PLab_PushButton rightButton(buttonPins[1]);// Push button object for Right.
PLab_PushButton upButton(buttonPins[2]);   // Push button object for Up.
PLab_PushButton downButton(buttonPins[3]); // Push button object for Down.

int ledPins[3][3] =                 // Arduino pins for the 3x3 LED matrix.
       {{5,6,7},
        {8,9,10},
        {11,12,13}}; 
        
boolean ledStatus[3][3] =     // Status of the 3x3 LED matrix. (LOW/HIGH).     
      {{LOW,LOW,LOW},
       {LOW,LOW,LOW},
       {LOW,LOW,LOW}};

int rabbitX = 0;  // X-position of the rabbit on the board.
int rabbitY = 0;  // Y-position of the rabbit on the board.
int rabbitDx;     // Direction of rabbit along x-axis  (dx = -1, 0 or 1)
int rabbitDy;     // Direction of rabbit along y-axis  (dy = -1, 0 or 1)

unsigned long timeOfLastMove = 0;  // What time was it when the rabbit last moved.
unsigned long currentTime = 0;     // The current time from the function millis().
int timeBetweenMoves = 1000;       // Start with 1 second between moves (jumps).
int numberOfMoves = 0;                 // Counter for no of moves made.

const int rows = 3, columns = 3;
const int movesToWin = 10;         // No of moves to win at a level is set to 10.

// restartGame is called initially and each time a level has been played,
// either by dying or by winning and going on to the next level.
void restartGame() {
  ledStatus[rabbitX][rabbitY] = LOW;  // Reset last position.
  rabbitX = 0;                        // Start in lower left corner (0,0).
  rabbitY = 0;
  ledStatus[0][0] = HIGH;   // Set LED for start positition to be HIGH (on).
  rabbitDx = 1;  // Start direction = right: (dx = 1, dy = 0)
  rabbitDy = 0;
  writeLEDStatus();             // update LEDs from ledStatus.
  numberOfMoves = 0;                // There have been no moves.
}

// Update LEDs based on the status of the table ledStatus[x][y].
void writeLEDStatus() {
 for (int x=0; x<3; x++) {    // For x = 0..2
   for (int y=0; y<3; y++) {    // For y = 0..2
      digitalWrite(ledPins[x][y], ledStatus[x][y]); // Set pin to status
   }
 }
} 

// Move the rabbit in the direction given by rabbitDx and rabbitDy.
// No LED update, only internally on the table ledStatus.
void moveRabbitTo(int newX, int newY) {   
   ledStatus[rabbitX][rabbitY] = LOW;  // Turn off LED for current position (X,Y).
   rabbitX = newX;
   rabbitY = newY;
   ledStatus[rabbitX][rabbitY] = HIGH;  // Turn on LED for new position (X,Y).   
}

// Set alle LED pins to a value (HIGH or LOW)
void setAllLEDsTo(int value) {
   for (int x=0; x<3; x++) {           // X = 0..2
     for (int y=0; y<3; y++) {         //   Y = 0..2
       digitalWrite(ledPins[x][y], value);  // Write value to pin (X,Y).
     }
   }
}

// Blink LEDs to indicate failure at this level.
void doDie() {
   for (int i=0; i<5; i++) {
     setAllLEDsTo(LOW);
     delay(200);
     setAllLEDsTo(HIGH);
     delay(200);
   }
}   
  
// Fill the LED matrix to indicate success at this level. 
void doWin() {
   for (int i=0; i<4; i++) {
     setAllLEDsTo(LOW);  
     delay(100);
     for (int x=0; x<3; x++) {
       for (int y=0; y<3; y++) {  
         digitalWrite(ledPins[x][y], HIGH);
         delay(100);
       }
     }
   }
} 


// Code to update the pushbutton objects from the Arduino input pins.
void updateButtons() {
   leftButton.update();
   rightButton.update();  
   upButton.update();
   downButton.update(); 
}

// Check if any of the fours buttons have been pressed. 
// If so, change direction of rabbit accordingly.
void checkForButtonPresses() {
  if (leftButton.pressed()) {          // Left button pressed -> (dx,dy) = (-1,0)
    rabbitDx = -1;
    rabbitDy = 0;  
  } else if (rightButton.pressed()) {  // Right button pressed -> (dx,dy) = (1,0)
    rabbitDx = 1;
    rabbitDy = 0;  
  } else if (upButton.pressed()) {     // Up button pressed -> (dx,dy) = (0,1)
    rabbitDx = 0;
    rabbitDy = 1;  
  } else if (downButton.pressed()) {   // Down button pressed -> (dx,dy) = (0,-1)
    rabbitDx = 0;
    rabbitDy = -1;  
  };
}

boolean isValidPosition(int x, int y) {
    return (x >= 0) && (x < columns) && (y >= 0) && (y < rows);
}

void tick() {  // Called when there is time to move
  int nextRabbitX = rabbitX + rabbitDx; 
  int nextRabbitY = rabbitY + rabbitDy;
  if (isValidPosition(nextRabbitX, nextRabbitY)) {   // If it will end up inside the board
    moveRabbitTo(nextRabbitX, nextRabbitY);
    writeLEDStatus();             // Update the LEDs from the table ledStatus
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
  for (int x=0; x<3; x++) {            // Set all LED pins to OUTPUT
   for (int y=0; y<3; y++) {  
      pinMode(ledPins[x][y], OUTPUT);
   }
  }
  for (int i=0; i<4; i++) {           // Set all button pins to INPUT
      pinMode(buttonPins[i], INPUT);
   }
  restartGame();                      // Restart the game.
  timeOfLastMove = millis();          // Start timing
}

// The loop is called again and again.
void loop() {
  updateButtons();          // Update the button objects.
  checkForButtonPresses();  // Check for button presses and change direction if pressed.
  currentTime = millis();   // What is the current time?
  if ((currentTime - timeOfLastMove) > timeBetweenMoves) { // If time for next move 
    tick();                       // Make one move
    timeOfLastMove = millis();    // Reset the timer.
  }
}

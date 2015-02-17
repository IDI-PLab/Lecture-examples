
/*
ZumoC is an animal that explores a closed world (inside a black border). 
The robot becomes hungry after some time, and starts
searching for food. If food (detection of food area) is found, it eats. 
Afterwards the robot continues walking around. 
Otherwise it dies. If it get enough food, the animal celebrates by following 
the border line with all LEDs on.
The Animal states are: wander, serach, eat, celebrate and die.
StartUp: Place the robot near border lines and food areas for calibration. 
Press button and the calibration starts.
Then place the robot inside the border and press user button once more. 
The robot moves around in state Wander and will
go into the different states after a while.

              
   Wiring:   green light = digital pin 0  (Ok and not hungry)
             yellow light = digital pin 1 (hungry and looking for food)
             red light   = digital pin 6  (dying)
*/
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>


#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     100
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms
#define CHECK_DURATION    200 // ms
#define LEFT 1  // turn direction
#define RIGHT 2
const int MAX_SPEED = 400;   // Max speed Zumo

// Instansiate sensor, motor and pushbutton objects
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

// Set constants for PID control
unsigned int sensors[6];
int lastError = 0;
const float KP = 0.5;  // Proportional constant
const float KD = 6;    // Derivative constant
const int SV = 2500; // Set-value for position (in the middle of sensors)

// Define thresholds for border and food area
#define FOOD_VALUE_LOW 200  // low value for food area
#define BORDER_VALUE_LOW  800 // border low
// Finding of food area is based on countings food or border detections 
// i.e sensor values above FOOD_VALUE_LOW and BORDER_VALUE_LOW
#define REQ_BORDER_DETECT_COUNT 3  // Required number of detections to be a border area (sensor 0 and 5)
#define REQ_FOOD_DETECT_COUNT 5    // Required number of detections to be a food area (sensor 0 and 5)
#define REQ_FOOD_DETECT_COUNT2 4  // Required number of detections to be a food area (sensor 1 and 4)

long int diffLeftRightSpeed = 0; // tells which way to turn and move to go inside border area

// Connections digital output to LEDs
const int greenLedPin = 0;
const int yellowLedPin = 1;
const int redLedPin = 6;
const int callibrateLedPin = 13;

// Define animal STATES 
int currentState;
#define WANDER 1
#define SEARCH 2
#define EAT 3
#define CELEBRATE 4
#define DIE 5
// Animal Attributes
#define MAXTIME_WITHOUT_FOOD 30000
#define TIME_UNTIL_HUNGRY 15000
long int timeWithoutFood;
long int timeMeal;
//
//  Setup for ZumoC 
//
void setup()
{
  // start state is WANDER  (just walk around and not hungry)
  currentState = WANDER;
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(callibrateLedPin, OUTPUT);
  
  // wait for button to start calibration
  button.waitForButton();
  doVisionCalibration();
  // Now the Zumoc can start exploring the world by pressing button once more
  button.waitForButton();
  // Zumoc has eaten
  timeMeal = millis(); 
  
}
//  Loop for Zumoc
//  -- HANDLE STATES AND TRANSITIONS
void loop()
{ // 
  //Handle state transitions and execute action to current state

  switch(currentState) {
  case WANDER: wander(); break;
  case SEARCH: search(); break;
  case EAT: eat(); break;
  case CELEBRATE: celebrate();break;
  case DIE: die(); break;
  }  
}


//  -- STATE: WANDER --
// A green led signals that the animal is in the wander-state.
// It stays in the state until it becomes hungry (switch to search for food state)
// It only reacts to borders (no food area)
void wander()
{
  unsigned int position = 0;
  boolean hungry = false;
  
  digitalWrite(greenLedPin, HIGH);
  delay(2000);
  while (not hungry){
   //  read new sensor values
   position = reflectanceSensors.readLine(sensors);
  
   // Check to see if the border line has been reach. If so, turn and move in other direction.
   if (sensors[0] > BORDER_VALUE_LOW ){
   // if leftmost sensor detects line, reverse and turn to the right 
    turn(RIGHT);
  }
  else if (sensors[5] > BORDER_VALUE_LOW){
   // if rightmost sensor detects line, reverse and turn to the left
    turn(LEFT);
  }else {
  // otherwise, go straight
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }  
 
  // Update time in state and check if hungry 
  timeWithoutFood = millis() - timeMeal;
  if (timeWithoutFood > TIME_UNTIL_HUNGRY) { 
    hungry = true;
    currentState = SEARCH; 
  } 
} // end while
    
   digitalWrite(greenLedPin, LOW);   
}


// -- STATE: SEARCH --
// A yellow LED signals that the Zumo Animal is in the search-for-food state
// It now moves around looking for food areas
//
void search(){
  unsigned int position = 0;
  int  border = 0;
  boolean dying = false, foodFound = false, borderLeftFound = false, borderRightFound=false; 
  digitalWrite(yellowLedPin, HIGH); // Signal state

  //Try to find food (area) before starving to death
  while (not dying && not foodFound) {
   // Read new sensor values
   position = reflectanceSensors.readLine(sensors);
   // Check sensors at both sides for detection of any border (black tape or food area)
   if (sensors[0] > FOOD_VALUE_LOW || sensors[5] > FOOD_VALUE_LOW) {
     long int timeDetect = millis();
     // Border detected - check if really area 
     int nBorderLeftDetect = 0, nBorderRightDetect = 0; 
     int nFoodDetect = 0, nFoodDetect2 = 0;
     //
     // Move into border or food area for checking further for decision
     // Count occurances of various areas detected
     while ((millis()-timeDetect) < CHECK_DURATION){ // Determins how far to move while checking
        position = reflectanceSensors.readLine(sensors);
        delay(20); // move a bit before next read
        // Count occurances of border and food DETECTIONS (sensor value).
        if (sensors[0] > BORDER_VALUE_LOW) {
          nBorderLeftDetect++; 
        } else if (sensors[5] > BORDER_VALUE_LOW) { 
          nBorderRightDetect++;
        } else {
          if (sensors[0] > FOOD_VALUE_LOW)  nFoodDetect++;  // Food probably detected by sensor
          if (sensors[1] > FOOD_VALUE_LOW)  nFoodDetect2++; // A second sensor has detected foodarea
          if (sensors[4] > FOOD_VALUE_LOW)  nFoodDetect2++;
          if (sensors[5] > FOOD_VALUE_LOW)  nFoodDetect++;
        }
     } // end  while checking
  
     // Decide if border or food area based on coutings, or just ignore (too few detections) 
     if (nBorderLeftDetect > REQ_BORDER_DETECT_COUNT){ // find out which way to turn
       turn(RIGHT);
     }else if (nBorderRightDetect > REQ_BORDER_DETECT_COUNT){
       turn(LEFT);
     } else if (nFoodDetect > REQ_FOOD_DETECT_COUNT ){
       if (nFoodDetect2 > REQ_FOOD_DETECT_COUNT2) foodFound = true; // Avoid moving nerly along line
     }      
  }else {
    // otherwise, go straight
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }  
  
  // Update time since last meal and heck if time has run out => dying is new state
  timeWithoutFood = millis()-timeMeal;
  if (timeWithoutFood > MAXTIME_WITHOUT_FOOD) {
    dying = true;
    currentState = DIE;
  }
} // end Outer while (time check hungry loop)

   if (foodFound) {
    // If food found then set new state to eat
    currentState = EAT;
   }   

  digitalWrite(yellowLedPin, LOW);
}


//  -- STATE: EAT --
// Eat food within food area (detected in serach state)
//
void eat() {
  
 // stop before eating 
  motors.setSpeeds(0,0);
  // Blink all LEDs when eating
  for (int i = 0; i < 500; i=i+30){ 
    // Put all LEDs on
    digitalWrite(yellowLedPin, HIGH);
    delay(500-i);
    // 
    digitalWrite(yellowLedPin, LOW); 
    delay(500-i);
  }
   if (random(100) > 50){ //enough food found
     // Finished eating, if enough food move to border and celebrate 
     currentState = CELEBRATE;
     motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
     // drive to line and stop before celebrating
     while (sensors[0] < BORDER_VALUE_LOW && sensors[5] < BORDER_VALUE_LOW)
          unsigned int position = reflectanceSensors.readLine(sensors);
     motors.setSpeeds(0,0); 
    // store time for this meal
   } else {
     //No reason for celebration: wander again
     currentState = WANDER;
   }
    timeMeal = millis();
}


//  STATE: CELEBRATE
// Behavior in state "celebrate": Find border line and follow for some time.
// Then return to inside area and make transition to state "Wander"

void celebrate() {
  diffLeftRightSpeed = 0;
  long int timeCelebrate = 10000; // time to be happy
  long int timeStartCelebrate = millis();
  
  
  digitalWrite(yellowLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH); 
  digitalWrite(redLedPin, HIGH);
  
  while (timeCelebrate > (millis()-timeStartCelebrate)) {
    int position = reflectanceSensors.readLine(sensors);
    // Our "error" is how far we are away from the center of the line, which
    // corresponds to position 2500.
    int error = position - SV;
    // do PD computation ( Integral is not used)
    int speedDifference = KP*error + KD * (error - lastError);
  
    lastError = error;

    // Get individual motor speeds.  The sign of speedDifference
    // determines if the robot turns left or right.
    int m1Speed = MAX_SPEED + speedDifference;
    int m2Speed = MAX_SPEED - speedDifference;
    // Find out which side is inside if circle (integrate speed difference)
    diffLeftRightSpeed = diffLeftRightSpeed + m1Speed - m2Speed;
  
    
  // Here we constrain our motor speeds to be between 0 and MAX_SPEED.
  // Generally speaking, one motor will always be turning at MAX_SPEED
  // and the other will be at MAX_SPEED-|speedDifference| if that is positive,
  // else it will be stationary.  For some applications, you might want to
  // allow the motor speed to go negative so that it can spin in reverse.
    if (m1Speed < 0)
      m1Speed = 0;
    if (m2Speed < 0)
      m2Speed = 0;
    if (m1Speed > MAX_SPEED)
      m1Speed = MAX_SPEED;
    if (m2Speed > MAX_SPEED)
      m2Speed = MAX_SPEED;

    motors.setSpeeds(m1Speed, m2Speed);
  }//end while
  // Finished celebration - stop and drive into area again (circle)
  // diffRightLeftSpeed tells which way to turn ( > 0 means turn right )
  motors.setSpeeds(0, 0);
  delay(2000);
  if (diffLeftRightSpeed > 0 ) { 
    // turn right
     motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
     delay(TURN_DURATION);
  } else{
    //turn left
     motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
     delay(TURN_DURATION);
  }
  motors.setSpeeds(0, 0);
  delay(2000);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  currentState = WANDER;
  timeMeal = millis();  // Celebrating takes time, but ignore with respect to meal
} 
//
//  -- STATE: DYING --
//     No food found: do behavior for dying
void die() {
  // Stop and turn red LED on.
  motors.setSpeeds(0, 0);
  digitalWrite(redLedPin, HIGH);
  delay(3000);
  digitalWrite(redLedPin, LOW);
  delay(3000);
  // Blink all LEDs while moving back and forth in decreasing frequency
  for(int i = 0; i < 200; i=i+20) { 
    // Put all LEDs on
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(greenLedPin, HIGH); 
    digitalWrite(redLedPin, HIGH);
    motors.setSpeeds(200-i, 200-i);
    delay(400-i);
    // Then all LEDs off
    digitalWrite(greenLedPin, LOW); 
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    motors.setSpeeds(i-200, i-200); 
    delay(400-i); 
    }
    
  digitalWrite(yellowLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH); 
  digitalWrite(redLedPin, HIGH);
  delay(3000);
  digitalWrite(greenLedPin, LOW); 
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  delay(30000);
}
//
// Move Zumo backwards, then turn in given direction,
// and continue forward
//
void turn(int direction){ 
   // Check wich direction to turn
   if (direction == RIGHT)
   {
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else // turn left
  {
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }  
}


void doVisionCalibration() {
//
// -- Rotates to calibrate IR-reflectance sensors 
//
   reflectanceSensors.init();
// Turn on LED to indicate we are in calibration mode
  pinMode(callibrateLedPin, OUTPUT);
  digitalWrite(callibrateLedPin, HIGH);

  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  int i;
  for(i = 0; i < 80; i++) {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
  
    reflectanceSensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  motors.setSpeeds(0,0);

  // Turn off LED to indicate we are through with calibration
  digitalWrite(callibrateLedPin, LOW);
  }

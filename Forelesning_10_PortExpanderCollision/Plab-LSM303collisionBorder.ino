/* Purpose: 
         When the zumo collides with an obstacle, it stops,putthe red LED on, and turns way randomly.
         It also turns when it encounter a black border
   
   This program is a modified copy and "simpler" version of Pololu´s found at:  
  
   
   https://github.com/pololu/zumo-shield/blob/master/ZumoExamples/examples/SumoCollisionDetect/SumoCollisionDetect.ino

   Our version is for IT1501/TDT4112 and is not object oriented or using the RunningAverage template as above. 

   
   Modifications programmed by: 
          Asbjørn Thomassen
           IDI, NTNU, 2017.
  
  In loop(), the program reads the x and y components of acceleration (ignoring z), and detects a
  contact when the magnitude of the 3-period average of the x-y vector exceeds an empirically determined
  XY_ACCELERATION_THRESHOLD.  On contact detection, the forward speed is increased to FULL_SPEED from
  the default SEARCH_SPEED, simulating a "fight or flight" response.
  
 
  The program attempts to detect contact only when the Zumo is going straight.  When it is executing a
  turn at the sumo ring border, the turn itself generates an acceleration in the x-y plane, so the 
  acceleration reading at that time is difficult to interpret for contact detection.  Since the Zumo also 
  accelerates forward out of a turn, the acceleration readings are also ignored for MIN_DELAY_AFTER_TURN 
  milliseconds after completing a turn. To further avoid false positives, a MIN_DELAY_BETWEEN_CONTACTS is 
  also specified.
 */

#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Wire.h>
#include <LSM303.h>

#define LED 13
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

// am Settings
#define SEQ_SIZE 3  // number of readings to include in running average of am readings 2400
#define XY_ACCELERATION_THRESHOLD 2400  // for detection of contact (~16000 = magnitude of acceleration due to gravity)

// Reflectance Sensor Settings
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1600 // 
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN); 

// Motor Settings
ZumoMotors motors;

// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define SEARCH_SPEED      200 // Default speed
#define SUSTAINED_SPEED   400 // switches to SUSTAINED_SPEED from FULL_SPEED after FULL_SPEED_DURATION_LIMIT
#define FULL_SPEED        400 // "fight or flight" speed response
#define STOP_DURATION     100 // ms
#define FULL_SPEED_DURATION_LIMIT     300  // ms  250
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms
#define RIGHT 1
#define LEFT -1

enum ForwardSpeed { SearchSpeed, SustainedSpeed, FullSpeed };
ForwardSpeed _forwardSpeed;  // current forward speed setting
 // Timing
unsigned long loop_start_time;
unsigned long last_turn_time;
unsigned long contact_made_time;
unsigned long full_speed_start_time;

#define MIN_DELAY_AFTER_TURN          400  // ms = min delay before detecting contact event
#define MIN_DELAY_BETWEEN_CONTACTS   1000  // ms = min delay between detecting new contact event

const int redLedPin = 6;  

 LSM303 am;
 boolean in_contact;
 
// 
// Record for return of accelerator data:
// Use ring buffer (lsm303_sequence) to remove false positive collision (filtering)
// Need also time to ignore false positives from turns and start of motors etc 

typedef struct lsm303_sequence {int cnt;   // numb of values currently in acceleration record (ring buffer)
              int idx; // index to put next value in ring buffer 
              unsigned long timestamp;  // time for last reading into buffer
              int value_x[SEQ_SIZE]; // acceleration values
              int value_y[SEQ_SIZE];  
              long sum_x; // x-sum of sequence 
              long sum_y; // y-sum of sequence 
              };
              
lsm303_sequence a_data;   // make sequence of accelaration data (ring buffer)

void init_read() 
// initialise data sequence (before storing data from lsm303)
{ 
  a_data.cnt = 0;
  a_data.timestamp = 0;
  a_data.idx = 0; 
  a_data.sum_x = 0;
  a_data.sum_y = 0;
  for (int i = 0; i< SEQ_SIZE; i++){ 
      a_data.value_x[i] = 0; 
      a_data.value_y[i] = 0; 
  }
}
void readDataLSM303(long timestamp) {
// Read values from LSM303 
    am.readAcc();  
// Data is now in am.a.x and am.a.y
// Put into sequence buffer 
    a_data.timestamp = timestamp;               // not used in current version
    a_data.sum_x -= a_data.value_x[a_data.idx]; // subtract value to be replaced from sum  
    a_data.sum_y -= a_data.value_y[a_data.idx];
    a_data.value_x[a_data.idx] = am.a.x; 
    a_data.value_y[a_data.idx] = am.a.y;
    a_data.sum_x += a_data.value_x[a_data.idx]; // add new value to sum
    a_data.sum_y += a_data.value_y[a_data.idx]; 
    //update ring buffer pointer
    a_data.idx++;
    if (a_data.idx == SEQ_SIZE) a_data.idx = 0;  // faster than %
    if (a_data.cnt < SEQ_SIZE) a_data.cnt++;  
}

long av_squared() 
{
  // compute average of sequence of with x and y readings (filter noisy readings)
  long x_avg = static_cast <long> (a_data.sum_x/(long) a_data.cnt);  
  long y_avg = static_cast <long> (a_data.sum_y/(long) a_data.cnt); 
  // return squared value of xy-vector
  return x_avg*x_avg + y_avg*y_avg;
}

bool check_for_contact()
{
// Check if a collision detect and that it´s not caused by a turn or by recently contact
    static long threshold_squared = \
              (long) XY_ACCELERATION_THRESHOLD * (long) XY_ACCELERATION_THRESHOLD;
              
    return (av_squared() >  threshold_squared) && \
    (loop_start_time - last_turn_time > MIN_DELAY_AFTER_TURN) && \
    (loop_start_time - contact_made_time > MIN_DELAY_BETWEEN_CONTACTS);  
}


void setForwardSpeed(ForwardSpeed speed)
{
  _forwardSpeed = speed;
  if (speed == FullSpeed) full_speed_start_time = loop_start_time;
}

int getForwardSpeed()
{
  int speed;
  switch (_forwardSpeed)
  {
    case FullSpeed:
      speed = FULL_SPEED;
      break;
    case SustainedSpeed:
      speed = SUSTAINED_SPEED;
      break;
    default:
      speed = SEARCH_SPEED;
      break;
  }
  return speed;
}
void on_contact_made()
{
  in_contact = true;
  
    setForwardSpeed(FullSpeed); 
    
 // Light LED to indicate collision, the stop and wait,
 // followed by turn right "randomly"
    digitalWrite(redLedPin, HIGH);
    motors.setSpeeds(0,0);
    delay(2000);
    digitalWrite(redLedPin, LOW);
    contact_made_time = loop_start_time;  
    turn(RIGHT, true);
}

void on_contact_lost()
{
  in_contact = false;
  // turn off LED
  digitalWrite(redLedPin, LOW); 
  setForwardSpeed(SearchSpeed);
}

void turn(char direction, bool randomize)
{
  // Assume contact lost
  on_contact_lost();
  // Do turn
  static unsigned int duration_increment = TURN_DURATION / 4;
  motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
  delay(REVERSE_DURATION);
  motors.setSpeeds(TURN_SPEED * direction, -TURN_SPEED * direction);
  delay(randomize ? TURN_DURATION + (random(8) - 2) * duration_increment : TURN_DURATION);
  //
  int speed = getForwardSpeed();
  motors.setSpeeds(speed, speed);
  // Change in driving direction may give false collisions
  // Set time to ignore collision while turning
  last_turn_time = millis(); 
}


void setup() {
// Set up I2C an serial communication
  Wire.begin();
  Serial.begin(9600);
//
// Initialise LSM303 (I2C)
  am.init();
  am.enableDefault();
// Init buffer to store acceleration data
  init_read(); 
//
  pinMode(redLedPin, OUTPUT);
  digitalWrite(redLedPin, HIGH);
  
  button.waitForButton();
  digitalWrite(redLedPin, LOW);
  randomSeed((unsigned int) millis());
 //
 // Time variables initialisation 
  in_contact = false;
  contact_made_time = 0;
  last_turn_time = millis();
  full_speed_start_time = 0;
  _forwardSpeed = SearchSpeed;
}

void loop() {
  loop_start_time = millis();
  readDataLSM303(loop_start_time); // read acceleration data into buffer
  sensors.read(sensor_values);
  
  if ((_forwardSpeed == FullSpeed) && \
      (loop_start_time - full_speed_start_time > FULL_SPEED_DURATION_LIMIT))
  { 
    setForwardSpeed(SustainedSpeed);
  }
  
  if (sensor_values[0] > QTR_THRESHOLD)
  {
    // if leftmost sensor detects line, reverse and turn to the right
    turn(RIGHT,true);
  }
  else if (sensor_values[5] > QTR_THRESHOLD)
  {
    // if rightmost sensor detects line, reverse and turn to the left
    turn(LEFT,true);
  }
  else  // otherwise, go straight if no collision
  {
    // check for contact and if so: do necessary action
    if (check_for_contact()) on_contact_made();
    //
    int speed = getForwardSpeed();
    motors.setSpeeds(speed, speed);
  }
}



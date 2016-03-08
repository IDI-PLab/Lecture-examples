/*
  ProximitySensor
  
  Dette er et eksempel på hvordan du kan bruke en HC-SR04 ultralyd sensor med biblioteket NewPing for å måle avstand.
  Lengde (i centimeter) måles og skrives ut hver 50 ms.
  
  Kretsen:
    1 x HC-SR04 (ultralyd sensor)
  Oppkobling vises på wiki:
  https://www.ntnu.no/wiki/display/plab/3.+Ultralyd+-+HC-SR04
  
  Bibliotek
    - NewPing (Nedlasting: https://code.google.com/p/arduino-new-ping/downloads/list )
  
  
  This is an example on how you may use a HC-SR04 ultrasonic sensor with the library NewPing to detect distance.
  Distance (in centimetres) is measured and printed every 50 ms.
  
  Circuit
    1 x HC-SR04 (ultrasonic sensor)
  How to connect circuit can be seen here:
  https://www.ntnu.no/wiki/display/plab/3.+Ultralyd+-+HC-SR04
  
  Library
    - NewPing (Download: https://code.google.com/p/arduino-new-ping/downloads/list )
 */
#include <NewPing.h>
#include <NewServo.h>
#include <Pushbutton.h>
#include <PLab_ZumoMotors.h>
#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

#define LED 13
 
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  1800 // 
  
// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     200

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;


ZumoMotors motors;

const int ledPin=A5;

const int echoPin = A4;
const int triggerPin = A4;
const int maxDistance = 40;

const int servoPin = 6;
 
NewPing sonar(triggerPin, echoPin, maxDistance);
NewServo myServo; 

Pushbutton button(ZUMO_BUTTON); 

int degreesServo = 0;
int degreesStep = 5;

PLab_ZumoMotors plab_Motors;

void setup() {
  sensors.init();
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  myServo.attach(servoPin); 
  myServo.write(90);
  button.waitForButton(); // start when button pressed
}

void stepServo() {
   degreesServo = degreesServo + degreesStep;
   if (degreesServo > 180) {
       degreesStep = -degreesStep;
       degreesServo = 180;
   } else if (degreesServo < 0) {
       degreesStep = -degreesStep;
       degreesServo = 0;
   } 
   myServo.write(degreesServo);
}

float sonarDistance() {
  // Gjør ett ping, og beregn avstanden
  unsigned int time = sonar.ping();
  float distance = sonar.convert_cm(time);
  Serial.println(distance);
  if (distance == 0.0) { // sonar gives zero when outside range
    // Turn off LED and just go forward
    digitalWrite(ledPin,LOW); 
   } else {
    digitalWrite(ledPin,HIGH);
   }
   return distance;
}

void loop() {
   stepServo();
   int distance = sonarDistance();
   if (distance > 0) {
      if (degreesServo > 90) {
         plab_Motors.turnLeft(FORWARD_SPEED,degreesServo-90);
      } else if (degreesServo < 90) {
        plab_Motors.turnRight(FORWARD_SPEED,90-degreesServo);
      };
      degreesServo = 90;
      myServo.write(degreesServo);
  //    plab_Motors.forward(FORWARD_SPEED, distance-5);
    };
   
   sensors.read(sensor_values);
   if (sensor_values[0] < QTR_THRESHOLD) {
     plab_Motors.backward(REVERSE_SPEED, 10);
     plab_Motors.turnRight(TURN_SPEED,90);
   } else if (sensor_values[5] < QTR_THRESHOLD) {
     plab_Motors.backward(REVERSE_SPEED, 10);
     plab_Motors.turnLeft(TURN_SPEED,90);
   }
   else
   {
    // otherwise, go straight
     motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
}



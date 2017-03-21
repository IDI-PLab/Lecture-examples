//  Purpose: Test LSM303´s accelerometer in Zumo. Writes x, y and z 
//           values in serial window
//
//  Programmed by
//      Asbjørn Thomassen 
//      IDI, NTNU - 2017
//
#include <Wire.h>     //I2C communication
#include <LSM303.h>  

LSM303 am; 
  

void setup() {
  // Initialize I2C and serial communication
  Wire.begin(); 
  Serial.begin(9600);
  //
  // initialize LSM303
  am.init();
  am.enableDefault();
}
void loop() {
  // Read acceleration
  am.readAcc();
  // Now the x,y and z values can be fetched 
  // from the am.a data structure
    Serial.print(am.a.x);
    Serial.print("-");
    Serial.print(am.a.y);
    Serial.print("-");
    Serial.print(am.a.z);
    Serial.println();
    delay(200);
}

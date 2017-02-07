/*
    ADXL345 Triple Axis Accelerometer. Simple Example.
    From: https://github.com/jarzebski/Arduino-ADXL345
    2017 Dag Svanaes
*/

#include <Wire.h>
#include <ADXL345.h>

ADXL345 accelerometer;


void setup(void) 
{
  Serial.begin(9600);

  // Initialize ADXL345
  Serial.println("Initialize ADXL345");
  if (!accelerometer.begin())
  {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    delay(500);
  }
   accelerometer.setRange(ADXL345_RANGE_16G);
}

void loop(void) 
{
  Vector norm = accelerometer.readNormalize();

  // Output normalized m/s^2
  Serial.print(" Xnorm = ");
  Serial.print(norm.XAxis);
  Serial.print(" Ynorm = ");
  Serial.print(norm.YAxis);
  Serial.print(" Znorm = ");
  Serial.print(norm.ZAxis);

  Serial.println();

  delay(100);
}

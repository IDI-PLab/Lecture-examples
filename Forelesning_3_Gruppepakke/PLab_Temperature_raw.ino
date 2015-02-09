//TMP35 Pin Variables
int sensorPin = A3; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
}
 
void loop()                     // run over and over again
{
 //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0 / 1024; 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 // now print out the temperature
 float temperatureC = (voltage) * 100 ;  //converting from 10 mv per degree wit 500 mV offset                                            //to degrees ((volatge - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 delay(1000);                                     //waiting a second
}

const int echoPin = 7;
const int triggerPin = 8;
 
void setup() {
  Serial.begin(9600);
  
  // Definer hvilken type de forskjellige pinnene er
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
 
void loop() {
  // Gjør ekkokallet
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
   
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
   
  digitalWrite(triggerPin, LOW);
  // Mål hvor lang tid det tar før ekkoet kommer tilbake
  long duration = pulseIn(echoPin, HIGH);
  // Regn ut avstanden
  float distance = duration * 0.00017;  
   
  Serial.println(distance);
  delay(1000);
}


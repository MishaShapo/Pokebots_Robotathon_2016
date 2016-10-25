#include <hcrs04.h>

#define PINTRIG PD_7
#define PINECHO PD_6

hcrs04 mySensor(PINTRIG, PINECHO);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Basic HC-SR04 Ultrasonic Sensor Example");
  mySensor.begin();
}

void loop() {
  // put your main code here, to run repeatedly: 
  float DISTANCE = mySensor.read(); 
  Serial.println((int)DISTANCE);
//  Serial.println(" cm");
  delay(50);
}

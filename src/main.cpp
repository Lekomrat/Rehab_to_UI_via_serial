#include "modules.h"
#include "communication.h"

void setup(){
  Serial.begin(9600);
  setupScales();
}

void loop(){
  sendSensorData();
  delay(1000);
}


#include "Arduino.h"

const byte START_MARKER = 0xA0;
const byte END_MARKER = 0xC0;

byte sensorData[6];

byte readValue(double tenzo_unit){
  byte scaledValue = ;
  return scaledValue;
}
byte valve = readValue(getLeftStopa1());

void sendSensorData(){
  Serial.write(START_MARKER);
  for (byte i = 0; i < 2; i++){
    sensorData[i] = readValue(i);
    Serial.write(sensorData[i]);
  }
  //byte checksum = calculateChecksum();
  //Serial.write(checksum);
  Serial.write(END_MARKER);
}
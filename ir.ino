#include <Arduino.h>
#include <Wire.h>


int readIR() {
  Wire.requestFrom(8, 1);
  while (Wire.available()) {
    irSensor = Wire.read();
    return irSensor;
  }
}
int irSetup() {
  Wire.begin();
}

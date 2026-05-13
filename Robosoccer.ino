#include <Arduino.h>
#include <Wire.h>

int irSensor = 0;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  Serial.println("STARTING");
  imuSetup();
  irSetup();
  ultrasonicSetup();
  limitSetup();
  motorSetup();
  reflectanceSetup();

  Serial.println("READY");

  //moveToGoal();
  
}

void loop() {
  //aimBall();

  //Serial.println(readIR());
  //defend();

  //moveToGoal();

  //faceGoal();

  //score();
  //move(0, -100, 0);
  //delay(500);
  //stop();
  Serial.println(readIR());
}




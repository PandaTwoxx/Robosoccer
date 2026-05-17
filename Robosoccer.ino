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
  //delay(5000);
  
}

void loop() {
  //aimBall();

  //Serial.println(readIR());
  //defend();

  //moveToGoal();

  //faceGoal();

  score();
  move(0, -100, 0);
  delay(2000);
  stop();
}
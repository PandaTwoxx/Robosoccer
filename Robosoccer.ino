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

  Serial.println("READY");

  //moveToGoal();
  
}

void loop() {
  //aimBall();

  //Serial.println(readIR());
  //defend();

  //moveToGoal();

  //faceGoal();

  score();

  // first value is speed of left-right, second is speed of forward-backward, third is rotation speed
  delay(2000);

}




#include <Arduino.h>
#include <Wire.h>

int irthingy;

void Goaliesetup() {
  Serial.begin(115200);
  Serial.println("STARTING GOALIE");
  imuSetup();
  irSetup();
  ultrasonicSetup();
  limitSetup();
  motorSetup();
  reflectanceSetup();
  Serial.println("READY GOALIE");
}

void Goalieloop() {
    while (readReflectance() == true){
      Serial.print("hi");
      irthingy = readIR();
      if (irthingy == 4 or irthingy == 5){
        move(50, 50, 0);
      } else if (irthingy == 10 or irthingy ==11){
        move(-50,-50, 0);
      } else if (irthingy == 9){
        move(-50, 0, 0);
      } else if (irthingy == 0){
        move(0, -50, 0);
      } else if (irthingy ==6){
        move(0, 50, 0);
      } else if (irthingy == 7 or irthingy == 8){
        move(-50, 50, 0);
      } else if (irthingy == 1 or irthingy == 2){
        move(50, -50, 0);
      } else if (irthingy ==3){
        move(50, 0, 0);
      } else{
        stop();
      }

    
  delay(2000);
    }
}
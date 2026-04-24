void faceGoal(){
  int x = readIMU();
  if(x < 0){
    move(0, 50, -50);
    Serial.println("turning right to goal");
  }else if(x > 0){
    move(0, 50, 50);
    Serial.println("turning left to goal");
  }

  Serial.println("Moving to goal");

  while(readIMU() > 5 || readIMU() < -5);
  stop();
}

int fieldWidth = 180;

void shiftToGoal(int distance){
  faceGoal();
  
  int sideStride = readUltrasonicL();
  int targetStride = fieldWidth / 2 - 4;
  if(sideStride > targetStride){
    move(50, 50, 0);
    while(readUltrasonicL() > targetStride){}
    stop();
  }else if(sideStride < targetStride){
    move(-50, 50, 0);
    while(readUltrasonicL() < targetStride){}
    stop();
  }
  move(0, 140, 0);
  while(readUltrasonicF() > distance){}
  stop();
}

void moveToGoal(){
  faceGoal();
  
  int frontStride = readUltrasonicF();
  while(frontStride > 45){
    shiftToGoal(frontStride-30);
    frontStride = readUltrasonicF();
  }

  shiftToGoal(15);
}

void moveAngle(int angle, int speed, int rotation){
  move(speed*cos(angle*PI/180), speed*sin(angle*PI/180), rotation);
}

void aimBall(){
  readIR();
  if(irSensor == 255) move(0, 50, 0);
  if(irSensor < 6){
    move(0, 0, -50);
  }else{
    move(0, 0, 50);
  }
  while(readIR() != 6){}
  stop();
}

void score(){
  getBall();
  moveToGoal();
}

void getBall(){
  aimBall();
  bool setNext = false;
  while(!limitPressed()){
    if(readIR() != 6){
      aimBall();
      move(0, 120, 0);
      delay(300);
    }else{
      delay(300);
    }
  }
  stop();
}

void defend(){
  while(true){
    if(irSensor == 255) continue;
    if(irSensor < 6){
      move(-50, 0, 0);
    }else{
      move(50, 0, 0);
    }
    while(readIR() != 6);
    stop();
    delay(500);
  }
}
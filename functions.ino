// code to detect ze blindspot issues

#define BLINDSPOT_CHECK 20
int irSamples[BLINDSPOT_CHECK];
int sampleIndex = 0;

void clearsamples() {
  sampleIndex = 0;
  for(int i = 0; i < BLINDSPOT_CHECK; i++) {
    irSamples[i] = -1;
  }
}

int getIRSpread() {
  int mi = 255, ma = 0;
  int count = 0;

  for(int i = 0; i < BLINDSPOT_CHECK; i++) {
    if(irSamples[i] >= 0 && irSamples[i] <= 11) {
      count++;
      if(irSamples[i] < mi) mi = irSamples[i];
      if(irSamples[i] > ma) ma = irSamples[i];
    }
  }
  
  if(count < 4) return 0;
  
  return ma - mi;
}

bool checkBlindSpot() {
  return getIRSpread() > 5;
}

void blindspot(){
  stop();
  move(0, 70, 0);
  delay(700);
  stop();
  clearsamples();
}

// code to score

bool faceGoal(){
  int x = readIMU();
  if(x < 0){
    move(0, 50, -50);
    Serial.println("turning right to goal");
  }else if(x > 0){
    move(0, 50, 50);
    Serial.println("turning left to goal");
  }

  Serial.println("Moving to goal");

  while((readIMU() > 5 || readIMU() < -5) && limitPressed());
  stop();
  return limitPressed();
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
  if(!faceGoal())return;
  
  int frontStride = readUltrasonicF();
  while(frontStride > 75){
    shiftToGoal(frontStride-30);
    frontStride = readUltrasonicF();
  }

  shiftToGoal(45);
}

void moveAngle(int angle, int speed, int rotation){
  move(speed*cos(angle*PI/180), speed*sin(angle*PI/180), rotation);
}

void aimBall(){
  clearsamples();
  readIR();
  int loopCount = 0;
  const int MAX_LOOPS = 150;
  while(readIR() != 6){
    int ir = readIR();

    irSamples[sampleIndex % BLINDSPOT_CHECK] = ir;
    sampleIndex++;

    if(checkBlindSpot() || loopCount > MAX_LOOPS){
      blindspot();
      loopCount = 0;
    }
    if(ir == 255) {
      move(0, 50, 0);
    } else if(ir < 6) {
      move(0, 0, 50);
    } else {
      move(0, 0, -50);
    }

    loopCount++;
    delay(20);
  }
  stop();
}

void score(){
  getBall();
  moveToGoal();
}

void getBall(){
  aimBall();
  bool setNext = false;
  int blindspotCount = 0;
  const int MAX_BLINDSPOTS = 5;
  while(!limitPressed()){
    int ir = readIR();
    irSamples[sampleIndex % BLINDSPOT_CHECK] = ir;
    sampleIndex++;
    if(ir != 6){
      if(checkBlindSpot() && blindspotCount < MAX_BLINDSPOTS){
        blindspot();
        blindspotCount++;
        continue;
      }
      aimBall();
      move(0, 120, 0);
      delay(300);
    }else{
      move(0, 120, 0);
      delay(100);
      blindspotCount = 0;
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
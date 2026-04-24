int motorDirectionA = 4;
int motorSpeedA = 3;
int motorDirectionB = 12;
int motorSpeedB = 11;
int motorDirectionC = 8;
int motorSpeedC = 5;
int motorDirectionD = 7;
int motorSpeedD = 6;

int motorSetup() {
  pinMode(motorDirectionA, OUTPUT);
  pinMode(motorSpeedA, OUTPUT);
  pinMode(motorDirectionB, OUTPUT);
  pinMode(motorSpeedB, OUTPUT);
  pinMode(motorDirectionC, OUTPUT);
  pinMode(motorSpeedC, OUTPUT);
  pinMode(motorDirectionD, OUTPUT);
  pinMode(motorSpeedD, OUTPUT);
}

void move(int Vx, int Vy, int Vw){
  int speed1 = (Vx * 0.5) + (Vy * -0.866) + Vw; //fl
  int speed2 = (Vx * -1) + (Vy * 0) + Vw; //b
  int speed3 = (Vx * 0.5) + (Vy * 0.866) + Vw; //fr

  setMotorSpeed(motorSpeedA, motorDirectionA, speed1);
  setMotorSpeed(motorSpeedB, motorDirectionB, speed2);
  setMotorSpeed(motorSpeedC, motorDirectionC, speed3);
}

void stop(){
  setMotorSpeed(motorSpeedA, motorDirectionA, 0);
  setMotorSpeed(motorSpeedB, motorDirectionB, 0);
  setMotorSpeed(motorSpeedC, motorDirectionC, 0);
}

void setMotorSpeed(int speedPin, int directionPin, float speed) {
  int pwm = constrain(abs(speed), 0, 255);
  bool dir = (speed >= 0);
  
  if(dir){
    digitalWrite(directionPin, HIGH);
  }else{
    digitalWrite(directionPin, LOW);
  }
  analogWrite(speedPin, pwm);
}
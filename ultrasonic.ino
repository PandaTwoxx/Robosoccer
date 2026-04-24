int trigPin = 9;
int echoPin = 2;

int readUltrasonicL(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  return duration / 29 / 2;
}

int readUltrasonicF(){
  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);

  long duration = pulseIn(A0, HIGH);

  return duration / 29 / 2;
}

int ultrasonicSetup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
}
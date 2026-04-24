size_t limitPin = A2;

bool limitPressed(){
  return digitalRead(limitPin) == LOW;
}


int limitSetup(){
  pinMode(limitPin, INPUT_PULLUP);
}
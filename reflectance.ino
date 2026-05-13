size_t lightsensor = A3;


int reflectanceSetup(){
  pinMode(lightsensor, INPUT);
}

int readReflectance(){
  if(analogRead(A3)>0){
    return true;
  }
  return false;


}
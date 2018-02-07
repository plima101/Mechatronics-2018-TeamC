void setup() {
  Serial.begin(9600); 
}

int IRPin = 0;

float getIRDistance(){
  float val = analogRead(IRPin)*.0049; 
  if(val > 1.15)
    return 12.48 - 3.03*val;

  if(val > .55)
    return 20.5 - 10*val;

  else
    return 26.5-25*val;
}
void loop() {
  Serial.println(getIRDistance());
}

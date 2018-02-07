/* Analog Read Interrupter
* -----------------------
*/

/* Analog Read Interrupter
* -----------------------
*/

int ruptPin = 11; // select the input pin for the interrupter
int state = 0; // variable to store the value coming from the sensor

void setup()
{
    pinMode(ruptPin, INPUT);
}

void loop()
{
  // read the state of the pushbutton value:
  state = digitalRead(ruptPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (ruptPin == HIGH) {
    Serial.print('closed');
  } else {
    Serial.print('open');
  }
}

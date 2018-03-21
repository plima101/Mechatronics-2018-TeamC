#include "cleaning_servos_driver.h"
#include "Arduino.h"
void cleaning_servos_setup(){
  pinMode(FRONT_CLEANING_SERVO, OUTPUT);
  analogWrite(FRONT_CLEANING_SERVO, 255);
}

void cleaning_lift_front(){
  analogWrite(FRONT_CLEANING_SERVO, 255); 
}

void cleaning_lower_front(){
  analogWrite(FRONT_CLEANING_SERVO, 0);
}

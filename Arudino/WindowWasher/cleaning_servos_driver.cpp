#include "cleaning_servos_driver.h"
#include "Arduino.h"
#include <Servo.h>

Servo myservo;

void cleaning_servos_setup(){
  
  myservo.attach(FRONT_CLEANING_SERVO);
  myservo.write(180);
}

void cleaning_lift_front(){
  myservo.write(180); 
}

void cleaning_lower_front(){
  myservo.write(0);
}

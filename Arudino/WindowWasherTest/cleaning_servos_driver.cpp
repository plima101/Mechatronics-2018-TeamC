#include "cleaning_servos_driver.h"
#include "Arduino.h"
#include <Servo.h>

#define UP_POS 90
#define DOWN_POS 180

Servo myservo;

void cleaning_servos_setup(){
  
  myservo.attach(FRONT_CLEANING_SERVO);

  myservo.write(UP_POS);
}

void cleaning_lift_front(){
  myservo.write(UP_POS); 
}

void cleaning_lower_front(){
  myservo.write(DOWN_POS);
}

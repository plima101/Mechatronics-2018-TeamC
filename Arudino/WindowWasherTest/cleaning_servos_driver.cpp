#include "cleaning_servos_driver.h"
#include "Arduino.h"
#include <Servo.h>

#define L_START 90
#define R_START 90

Servo left_servo;
Servo right_servo;
void cleaning_servos_setup(){
  
  left_servo.attach(FRONT_LEFT_SERVO);
  right_servo.attach(FRONT_RIGHT_SERVO);

  left_servo.write(L_START);
  right_servo.write(R_START);
}

void cleaning_lift_front(){
  left_servo.write(L_START);
  right_servo.write(R_START); 
}

void cleaning_lower_front(){
  left_servo.write(L_START-90);
  right_servo.write(R_START+90); 
}

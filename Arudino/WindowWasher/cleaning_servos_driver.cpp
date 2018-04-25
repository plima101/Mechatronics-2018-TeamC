#include "cleaning_servos_driver.h"
#include "Arduino.h"
#include <Servo.h>

#define F_DOWN 30
#define F_UP 75
#define F_INIT 90

Servo front_servo;
void cleaning_servos_setup(){
  front_servo.attach(FRONT_SERVO);
  front_servo.write(F_INIT);
}

void cleaning_lift_front(){
  front_servo.write(F_UP); 
}

void cleaning_lower_front(){
  front_servo.write(F_DOWN);
}

#include "arm_motor_driver.h"
#include "Arduino.h"
void arm_motor_setup(){
  pinMode(RIGHT_ARM_IN1, OUTPUT);
  pinMode(RIGHT_ARM_IN2, OUTPUT);
  digitalWrite(RIGHT_ARM_IN1, LOW);
  digitalWrite(RIGHT_ARM_IN2, LOW);
}

void arm_motor_extend(bool left_extend, bool right_extend){
  if(right_extend){
    digitalWrite(RIGHT_ARM_IN1, HIGH);
    digitalWrite(RIGHT_ARM_IN2, LOW);
  }
}

void arm_motor_stop(bool left_stop, bool right_stop){
  if(right_stop){
    digitalWrite(RIGHT_ARM_IN1, LOW);
    digitalWrite(RIGHT_ARM_IN2, LOW);
  }
}

void arm_motor_retract(bool left_retract, bool right_retract){
  if(right_retract){
    digitalWrite(RIGHT_ARM_IN1, LOW);
    digitalWrite(RIGHT_ARM_IN2, HIGH);
  }
}

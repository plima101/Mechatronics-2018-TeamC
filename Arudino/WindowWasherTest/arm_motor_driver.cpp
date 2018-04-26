#include "arm_motor_driver.h"
#include "Arduino.h"
void arm_motor_setup(){
  pinMode(RIGHT_ARM_IN1, OUTPUT);
  pinMode(RIGHT_ARM_IN2, OUTPUT);
  pinMode(RIGHT_ARM_EN, OUTPUT);
  digitalWrite(RIGHT_ARM_EN, LOW);
  digitalWrite(RIGHT_ARM_IN1, LOW);
  digitalWrite(RIGHT_ARM_IN2, LOW);

  pinMode(LEFT_ARM_IN1, OUTPUT);
  pinMode(LEFT_ARM_IN2, OUTPUT);
  pinMode(LEFT_ARM_EN, OUTPUT);
  digitalWrite(LEFT_ARM_EN, LOW);
  digitalWrite(LEFT_ARM_IN1, LOW);
  digitalWrite(LEFT_ARM_IN2, LOW);


}

void arm_motor_extend(bool left_extend, bool right_extend){
  if(right_extend){
    digitalWrite(RIGHT_ARM_IN1, LOW);
    digitalWrite(RIGHT_ARM_IN2, HIGH);
    digitalWrite(RIGHT_ARM_EN, HIGH);   
  }
  if(left_extend){
    digitalWrite(LEFT_ARM_IN1, LOW);
    digitalWrite(LEFT_ARM_IN2, HIGH);
    digitalWrite(LEFT_ARM_EN, HIGH);   
  }

}

void arm_motor_stop(bool left_stop, bool right_stop){
  if(right_stop){
    digitalWrite(RIGHT_ARM_IN1, LOW);
    digitalWrite(RIGHT_ARM_IN2, LOW);
    digitalWrite(RIGHT_ARM_EN, LOW);
  }
  if(left_stop){
    digitalWrite(LEFT_ARM_IN1, LOW);
    digitalWrite(LEFT_ARM_IN2, LOW);
    digitalWrite(LEFT_ARM_EN, LOW);
  }
}

void arm_motor_retract(bool left_retract, bool right_retract){
  if(right_retract){
    digitalWrite(RIGHT_ARM_IN1, HIGH);
    digitalWrite(RIGHT_ARM_IN2, LOW);
    digitalWrite(RIGHT_ARM_EN, HIGH);   
  }
  if(left_retract){
    digitalWrite(LEFT_ARM_IN1, HIGH);
    digitalWrite(LEFT_ARM_IN2, LOW);
    digitalWrite(LEFT_ARM_EN, HIGH);   
  }
}


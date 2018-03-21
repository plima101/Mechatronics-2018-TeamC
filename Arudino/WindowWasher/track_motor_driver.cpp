#include "track_motor_driver.h"
#include "Arduino.h"
long rightPos, leftPos;

void update_right(){
  //if(digitalRead(RIGHT_TRACK_B)==HIGH)
    rightPos++;
  
 // else
    //rightPos--; 
}

void track_motor_setup(){
  leftPos = 0;
  rightPos = 0;
  pinMode(RIGHT_TRACK_IN1, OUTPUT);
  pinMode(RIGHT_TRACK_IN2, OUTPUT);
  pinMode(RIGHT_TRACK_A, INPUT);
  pinMode(RIGHT_TRACK_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(RIGHT_TRACK_A), update_right, RISING);
}

void track_motor_enable(){
  digitalWrite(RIGHT_TRACK_IN1, HIGH);
  digitalWrite(RIGHT_TRACK_IN2, LOW);
}

void track_motor_stop(){
  digitalWrite(RIGHT_TRACK_IN1, LOW);
  digitalWrite(RIGHT_TRACK_IN2, LOW);
}

void track_motor_pid(double left_target, double right_target){
  return;
}

void track_motor_pos(long* left_pos, long* right_pos){
  *left_pos = leftPos;
  *right_pos = rightPos;
}




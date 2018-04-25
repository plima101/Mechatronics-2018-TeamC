#include "track_motor_driver.h"
#include "Arduino.h"
long leftTarget, rightTarget, leftAtTarget, rightAtTarget;
long rightPos, leftPos;
double rightPWM, leftPWM;
long prevRightPos, prevLeftPos;
double last_time;
double left_speed, right_speed;
double left_ep = 0.0;
double left_et = 0.0;
double left_e = 0.0;
double left_P = 50.0;
double left_I = 0;
double left_D = 0;

double right_ep = 0.0;
double right_et = 0.0;
double right_e = 0.0;
double right_P = 50.0;
double right_I = 0.0;
double right_D = 0.0;

//Pin 5, RIGHT_TRACK_B is PORT E3
//Pin 4, LEFT_TRACK_B is PORT G5
  
void update_right(){
  //if(digitalRead(RIGHT_TRACK_B)==HIGH)
  if(PORTE & (1<<3))
    rightPos--;
  else
    rightPos++; 

  if(rightPos >= rightTarget){
    if(!rightAtTarget){
      rightAtTarget = 1;
      track_motor_stop(0,1);
    }
  }
}

void update_left(){
  //if(digitalRead(LEFT_TRACK_B)==HIGH)
  if(PORTG & (1<<5))  
    leftPos--;
  
  else
    leftPos++;

  if(leftPos >= leftTarget){
    if(!leftAtTarget){
      leftAtTarget = 1;
      track_motor_stop(1,0);
    }
  }
}

void track_motor_setup(){
  leftPos = 0;
  rightPos = 0;
  prevLeftPos = 0;
  prevRightPos = 0;
  leftPWM = 0;
  rightPWM = 0;
  last_time = millis();
  leftAtTarget = 0;
  leftTarget = 0;
  rightTarget = 0;
  rightAtTarget = 0;
  pinMode(RIGHT_TRACK_IN1, OUTPUT);
  pinMode(RIGHT_TRACK_IN2, OUTPUT);
  pinMode(RIGHT_TRACK_A, INPUT);
  pinMode(RIGHT_TRACK_B, INPUT);
  pinMode(RIGHT_TRACK_PWM, OUTPUT);
  pinMode(LEFT_TRACK_IN1, OUTPUT);
  pinMode(LEFT_TRACK_IN2, OUTPUT);
  pinMode(LEFT_TRACK_A, INPUT);
  pinMode(LEFT_TRACK_B, INPUT);
  pinMode(LEFT_TRACK_PWM, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(RIGHT_TRACK_A), update_right, RISING);
  attachInterrupt(digitalPinToInterrupt(LEFT_TRACK_A), update_left, RISING);
}

void track_motor_enable(){
  digitalWrite(RIGHT_TRACK_IN1, HIGH);
  digitalWrite(RIGHT_TRACK_IN2, LOW);

  digitalWrite(LEFT_TRACK_IN1, LOW);
  digitalWrite(LEFT_TRACK_IN2, HIGH);
}

void track_motor_stop(long left_stop, long right_stop){
  if(right_stop){
  digitalWrite(RIGHT_TRACK_IN1, LOW);
  digitalWrite(RIGHT_TRACK_IN2, LOW);
  analogWrite(RIGHT_TRACK_PWM, 0);
  }
  if(left_stop){
  digitalWrite(LEFT_TRACK_IN1, LOW);
  digitalWrite(LEFT_TRACK_IN2, LOW);
  analogWrite(LEFT_TRACK_PWM, 0);
  }
}


void track_motor_pid(double left_target, double right_target){
  double timeChange = ((double)millis() - last_time);
  while(!timeChange) timeChange = ((double)millis() - last_time);
  left_speed = (double)(leftPos - prevLeftPos)/timeChange;
  right_speed = (double)(rightPos - prevRightPos)/timeChange;
  
  left_e = left_target - left_speed;
  right_e = right_target - right_speed;

  double s = 1.0/(timeChange);

  leftPWM = leftPWM + left_e*left_P + (left_e-left_ep)*(1.0/s)*left_D + s*left_I*left_et;
  if(leftPWM > 255) leftPWM = 255;
  if(leftPWM < 0) leftPWM = 0;

  rightPWM = rightPWM + right_e*right_P + (right_e-right_ep)*(1.0/s)*right_D + s*right_I*right_et;
  if(rightPWM > 255) rightPWM = 255;
  if(rightPWM < 0) rightPWM = 0;
  
  Serial.println(leftPWM);
  analogWrite(LEFT_TRACK_PWM, (int)leftPWM);
  analogWrite(RIGHT_TRACK_PWM, (int)rightPWM);

  //update error and time counts
  left_ep = left_e;
  left_et = left_et + left_e;

  right_ep = right_e;
  right_et = right_et + right_e;



  last_time = millis();
  prevRightPos = rightPos;
  prevLeftPos = leftPos;



}

void track_motor_pos(long* left_pos, long* right_pos){
  *left_pos = leftPos;
  *right_pos = rightPos;
}

void update_targets(long left_target, long right_target){
  leftTarget = left_target;
  rightTarget = right_target;
  return;
}

long at_targets(){
  return leftAtTarget && rightAtTarget;
}

void reset_targets(){
  leftAtTarget = 0;
  rightAtTarget = 0;
}

void track_clear_pos(){
  leftPos = 0;
  rightPos = 0;
}



/*
 * Main application for Window Washer Robot
 * Authors: Mechantronics Team C: Millipede 
 * Date: 2/28/18
 */

/** BEGIN Header Files **/
//All macro definitions for pins used on Arduino Mega
#include "pins.h" 

//Functions to setup and drive motors for arm extension/retraction
#include "arm_motor_driver.h" 

//Functions to setup and drive motors using PID of chosen speed
#include "track_motor_driver.h" 

//Function to get distance to reference object (ground)
#include "ping_distance.h" 

//Functions to setup and read from accelermoter on chosen
#include "accelerometer.h"

//Functions to to drive front/back servos 
#include "cleaning_servos_driver.h"

#include "states.h"
 
/** END Header Files*/

/** BEGIN Debug Section */
//Uncomment Line below for Debug Serial Printing
#define DEBUG

#ifdef DEBUG
 #define DEBUG_START Serial.begin(9600)
 #define DEBUG_PRINT(x)  Serial.print (x)
 #define DEBUG_PRINTLN(x)  Serial.println (x)
 #define DEBUG_PRINTSTATE(x) Serial.print("The current State is "); Serial.println (x)
#else
 #define DEBUG_START
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
 #define DEBUG_PRINTSTATE(x)
#endif
/** END Debug Section */

#define BumpLength 50
#define VehicleLength 50
#define WindowLength 200
#define CUP_LENGTH 3456

long leftTargetLocal, rightTargetLocal;
long currentState;
long loopTics;
long barrierCrossed;
/*
 * For Demo on 3/21: Leds for motors, Micro Sevos, Limit Switches, Wire Encoder
 */

int cupMoved;

void setup() {
  pinMode(RIGHT_ARM_EXTENDED, INPUT_PULLUP);
  pinMode(RIGHT_ARM_RETRACTED, INPUT_PULLUP);
  pinMode(FRONT_BUMPER_LIMIT, INPUT_PULLUP);
  digitalWrite(LEFT_RELAY, HIGH);
  digitalWrite(RIGHT_RELAY, HIGH);
  pinMode(LEFT_RELAY, OUTPUT);
  pinMode(RIGHT_RELAY, OUTPUT);
  DEBUG_START;
  cleaning_servos_setup();
  track_motor_setup();
  update_targets(100000,100000);
  reset_targets();
  track_motor_enable();
  track_motor_pid(0.0, .5);
  while(digitalRead(FRONT_BUMPER_LIMIT) == LOW){
    delay(20);
    track_motor_pid(0.0, .5);
  }
  track_motor_stop(0, 1);
  delay(500);
  track_motor_pid(0.5, 0.0);
  while(digitalRead(FRONT_BUMPER_LIMIT) == LOW){
    delay(20);
    track_motor_pid(0.5, 0.0);
  }
  track_motor_stop(1,1);
  delay(500);
  while(digitalRead(FRONT_BUMPER_LIMIT) == LOW){
    delay(20);
  }
  delay(500);
  track_clear_pos();
  leftTargetLocal = CUP_LENGTH;
  rightTargetLocal = CUP_LENGTH;
  update_targets(leftTargetLocal, rightTargetLocal);
  lower_scrapers();
  cleaning_lower_front();
  arm_motor_setup();
  track_motor_enable();
  armClean();

  cupMoved = 0;
}

long leftPoslocal, rightPoslocal;

void loop() {
  
  if(at_targets()){
    cleaning_lift_front();
    delay(100);
    track_motor_pos(&leftPoslocal, &rightPoslocal);
    
    push_scrapers();
    delay(1000);
    lift_scrapers();
    delay(100);
    push_scrapers();
    delay(1000);
    lower_scrapers();
    
    cupMoved++;
    if (cupMoved % 4 == 0) {
      armClean();
    }
    
    leftTargetLocal += CUP_LENGTH;
    rightTargetLocal += CUP_LENGTH;
    update_targets(leftTargetLocal, rightTargetLocal);
    reset_targets();
    cleaning_lower_front();
    track_motor_enable();
  }
  else{
    track_motor_pos(&leftPoslocal, &rightPoslocal);
    DEBUG_PRINTLN(leftPoslocal);
    DEBUG_PRINTLN(rightPoslocal);
    track_motor_pid(.5, .5);
    delay(50);
  }
  /*
  while(digitalRead(FRONT_BUMPER_LIMIT) == LOW){
    delay(20);
  }
  lower_scrapers();
  delay(500);
  while(digitalRead(FRONT_BUMPER_LIMIT) == LOW){
    delay(20);
  }
  push_scrapers();
  delay(500);
  while(digitalRead(FRONT_BUMPER_LIMIT) == LOW){
    delay(20);
  }
  lift_scrapers();
  delay(500);
  */
  /*
  arm_motor_stop(true,true);
  while(digitalRead(FRONT_BUMPER_LIMIT) == LOW){
    delay(100);
  }
  arm_motor_extend(true,true);
  while(digitalRead(FRONT_BUMPER_LIMIT) == LOW){
    delay(100);
  }
  arm_motor_stop(true,true);
  while(digitalRead(FRONT_BUMPER_LIMIT) == LOW){
    delay(100);
  }
  arm_motor_retract(true,true);
  while(digitalRead(FRONT_BUMPER_LIMIT) == LOW){
    delay(100);
  }
  */
}

void armClean() {
  arm_motor_stop(true,true);
  delay(500);
  arm_motor_extend(true,true);
  delay(1400);
  arm_motor_stop(true,true);
  delay(500);
  arm_motor_retract(true,true);
  delay(1400);  
  arm_motor_stop(true,true);
}
  


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

//Functions to to drive front/back servos 
#include "cleaning_servos_driver.h"

#include "states.h"
 
/** END Header Files*/

/** BEGIN Debug Section */
//Uncomment Line below for Debug Serial Prlonging
#define DEBUG

#ifdef DEBUG
 #define DEBUG_START Serial.begin(9600)
 #define DEBUG_PRINT(x)  Serial.print (x)
 #define DEBUG_PRINTLN(x)  Serial.print (x)
 #define DEBUG_PRINTSTATE(x) Serial.print("The current State is "); Serial.print (x)
#else
 #define DEBUG_START
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
 #define DEBUG_PRINTSTATE(x)
#endif
/** END Debug Section */

#define BumpLength 1728
#define MiddleLength 18432
#define PadLength 4032
#define CUP_LENGTH 3456

#define B_FREE 0
#define B_FRONT 1
#define B_MIDDLE 2
#define B_BACK 3
#define B_AFTER 4
#define B_PAD 5

long leftTargetLocal, rightTargetLocal;
long currentState;
long loopTics;
long barrierCrossed;
long barrierHit;
/*
 * For Demo on 3/21: Leds for motors, Micro Sevos, Limit Switches, Wire Encoder
 */

long cupMoved;

void setup() {
  Serial.begin(9600);
  barrierHit = B_FREE;
  pinMode(FRONT_BUMPER_LIMIT, INPUT_PULLUP);
  DEBUG_START;
  cleaning_servos_setup();
  track_motor_setup();
  update_targets(10000,10000);
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
  //lower_scrapers();
  cleaning_lower_front();
  arm_motor_setup();
  track_motor_enable();
  armClean();

  cupMoved = 0;
}

long leftPoslocal, rightPoslocal;
long barrierTics;
void loop() {
  track_motor_pos(&leftPoslocal, &rightPoslocal);
  
  if(digitalRead(FRONT_BUMPER_LIMIT) == HIGH){
    track_motor_stop(1,1);
    armClean();  
    barrierHit = B_FRONT;
    cleaning_lift_front();
    delay(300);
    track_motor_pos(&leftPoslocal, &rightPoslocal);
    barrierTics = leftPoslocal;
    track_motor_enable();
  }
  
  if(at_targets()){
    
    if(barrierHit == B_FREE || barrierHit == B_PAD || barrierHit == B_MIDDLE || barrierHit == B_AFTER)
      sealCup();
      
    cupMoved++;
    if (cupMoved % 2 == 0) {
      if(barrierHit == B_FREE || barrierHit == B_AFTER) armClean();
    }
    advanceTarget();
  }
  else{
    track_motor_pid(.5, .5);
    if(barrierHit == B_FRONT && leftPoslocal - barrierTics >= PadLength/3){
      track_motor_stop(1,1);
      cleaning_lower_front();
      track_motor_enable();
      barrierHit = B_PAD;  
    }
    if(barrierHit == B_PAD && leftPoslocal - barrierTics >= PadLength + BumpLength){
      track_motor_stop(1,1);
      track_motor_enable();
      barrierHit = B_MIDDLE;  
    }
     
    if(barrierHit == B_MIDDLE && leftPoslocal - barrierTics >= PadLength + BumpLength + MiddleLength){
      track_motor_stop(1,1);
      lift_scrapers();
      track_motor_enable();
      barrierHit = B_BACK;
    }
    if(barrierHit == B_BACK && leftPoslocal - barrierTics >= 2*PadLength + BumpLength + MiddleLength){
      track_motor_stop(1,1);
      lower_scrapers();
      armClean();
      track_motor_enable();
      barrierHit = B_AFTER;
      cupMoved = 1;
    }
    delay(50);
  }
}

void armClean() {
  arm_motor_stop(true,true);
  delay(500);
  arm_motor_extend(true,true);
  delay(9000);
  arm_motor_stop(true,true);
  delay(500);
  arm_motor_retract(true,true);
  delay(9000);  
  arm_motor_stop(true,true);
}
  
void sealCup(){
    cleaning_lift_front();
    delay(100);
    push_scrapers();
    delay(1000);
    lift_scrapers();
    delay(100);
    push_scrapers();
    delay(1000);
    lower_scrapers();
    cleaning_lower_front();
}

void advanceTarget(){
  leftTargetLocal += CUP_LENGTH;
  rightTargetLocal += CUP_LENGTH;
  update_targets(leftTargetLocal, rightTargetLocal);
  reset_targets();
  track_motor_enable();
}


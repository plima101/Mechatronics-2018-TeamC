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

#define BumpLength 1728
#define MiddleLength 18432
#define PadLength 4032
#define CUP_LENGTH 3456



long currentState;
long loopTics;
long barrierCrossing;
long barrierCrossed; 
long barrierTics;
long frontCrossing, middleCrossing, backCrossing;
long leftTargetLocal, rightTargetLocal;

/*
 * For Demo on 3/21: Leds for motors, Micro Sevos, Limit Switches, Wire Encoder
 */

void setup() {
  pinMode(FRONT_BUMPER_LIMIT, INPUT_PULLUP);
  leftTargetLocal = 0;
  rightTargetLocal = 0;
  cleaning_servos_setup();
  track_motor_setup();
  arm_motor_setup();

  barrierCrossed = 0;
  barrierCrossing = 0;
  barrierTics = 0; 

  update_targets(100000, 100000);
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
  update_targets(CUP_LENGTH, CUP_LENGTH); 
  DEBUG_START;
  currentState = InitState;
  DEBUG_PRINTSTATE("InitState");
}

void loop() {
  int left_temp, right_temp;
  long *left_pos, *right_pos;
  track_motor_pos(left_pos, right_pos);
  if(at_targets()){
    leftTargetLocal += CUP_LENGTH;
    rightTargetLocal += CUP_LENGTH;
    update_targets(leftTargetLocal, rightTargetLocal);
    reset_targets();
    if(barrierCrossing && (frontCrossing || backCrossing)){
        track_motor_enable();
    }
    cleaning_lift_front();
    delay(100); 
    push_scrapers();
    delay(1000);
    lift_scrapers();
    delay(100);
    push_scrapers();
    delay(1000);
    lower_scrapers();
    track_motor_enable();
  }
    
  switch (currentState) {
    case InitState:
    loopTics = *right_pos;
    break;
    

    case RunArms:
    barrierCrossing = 0;
    loopTics = *right_pos;
    track_motor_stop(1,1);
    arm_run();
    break;
    
    
    case MoveForward:
    barrierTics = *right_pos;
    arm_motor_stop(1, 1);
    track_motor_enable();
    track_motor_pid(.5,.5);
    break;
    
    case BumpRunArms:
    loopTics = *right_pos;
    track_motor_stop(1,1);
    arm_run();
    break;

    case MoveOverBump:
    
    if(*right_pos - barrierTics <= PadLength + BumpLength){
        frontCrossing = 1;
        cleaning_lift_front();
    }
    else{
        frontCrossing = 0;
        cleaning_lower_front();
    }
    
    if(*right_pos - barrierTics >= PadLength + BumpLength + MiddleLength){
        backCrossing = 1;
        lift_scrapers();
    }
    else{
        backCrossing = 0;
        lower_scrapers();
    }
    arm_motor_stop(1,1);
    track_motor_enable();
    track_motor_pid(.5,.5);
    barrierCrossed = 1;
    barrierCrossing = 1;
    break;
    
    case FinalRunArms:
    track_motor_stop(1,1);
    arm_run();
    break;

    case SystemStop:
    track_motor_stop(1,1);
    arm_motor_stop(1, 1);
    break;
    
    default:
    //error
    break;
  }
  

  //next state logic
  switch (currentState) {
    case InitState:
    
    if(digitalRead(FRONT_BUMPER_LIMIT) == HIGH){
      currentState = RunArms;
      DEBUG_PRINTSTATE("RunArms");
    }
    break;
    
    case RunArms:
    currentState = MoveForward;
    DEBUG_PRINTSTATE("MoveForward");
    break;
    
    case MoveForward:
    track_motor_pos(left_pos, right_pos);
    if(!barrierCrossed && digitalRead(FRONT_BUMPER_LIMIT) == HIGH){
      currentState = BumpRunArms;
      DEBUG_PRINTSTATE("BumpExtendArms");
    }
    else if(*right_pos - loopTics >= 4*CUP_LENGTH){
      currentState = RunArms;
      DEBUG_PRINTSTATE("ExtendArms");
    }

    else if(barrierCrossed && digitalRead(FRONT_BUMPER_LIMIT) == HIGH){
      currentState = FinalRunArms;
      DEBUG_PRINTSTATE("FinalExtendArms");
    }
    break;
    
    case BumpRunArms:
      currentState = MoveOverBump;
      DEBUG_PRINTSTATE("BumpRunArms");
    break;
    
    case MoveOverBump:
    track_motor_pos(left_pos, right_pos);
    if(*right_pos - loopTics >= MiddleLength + BumpLength + 2*PadLength){
      currentState = RunArms;
      DEBUG_PRINTSTATE("RunArms");
    }
    break;
    
    case FinalRunArms:
      currentState = SystemStop;
    break;
    
    case SystemStop:
    break;
    
    default:
    //error
    break;
  }
  delay(50);
}

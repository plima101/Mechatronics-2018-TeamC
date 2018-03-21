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

//Functions to drive track servo
#include "track_servo_driver.h"

//Functions to to drive front/back servos 
#include "cleaning_servos_driver.h"
 
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

enum State {InitState, ExtendArms, RetractArms, MoveForward, BumpExtendArms, 
            BumpRetractArms, MoveOverBump, FinalExtendArms, FinalRetractArms, SystemStop};
State currentState;
long loopTics;
bool barrierCrossed;
/*
 * For Demo on 3/21: Leds for motors, Micro Sevos, Limit Switches, Wire Encoder
 */

void setup() {
  pinMode(RIGHT_ARM_EXTENDED, INPUT_PULLUP);
  pinMode(RIGHT_ARM_RETRACTED, INPUT_PULLUP);
  pinMode(FRONT_BUMPER_LIMIT, INPUT_PULLUP);

  cleaning_servos_setup();
  track_motor_setup();
  arm_motor_setup();

  barrierCrossed = 0;
  DEBUG_START;
  currentState = InitState;
  DEBUG_PRINTSTATE("InitState");
}

void loop() {
  long *left_pos, *right_pos;
  track_motor_pos(left_pos, right_pos);
  switch (currentState) {
    case InitState:
    loopTics = *right_pos;
    break;
    
    case ExtendArms:
    loopTics = *right_pos;
    track_motor_stop();
    arm_motor_extend(1, 1);
    break;
    
    case RetractArms:
    arm_motor_retract(1, 1);
    break;
    
    case MoveForward:
    arm_motor_stop(1, 1);
    track_motor_enable();
    //track_servo_restore();
    cleaning_lower_front();
    break;
    
    case BumpExtendArms:
    track_motor_stop();
    arm_motor_extend(1,1);
    loopTics = *right_pos;
    break;
    
    case BumpRetractArms:
    arm_motor_retract(1,1);
    break;
    
    case MoveOverBump:
    cleaning_lift_front();
    //track_servo_release();
    track_motor_enable();
    barrierCrossed = 1;
    break;
    
    case FinalExtendArms:
    track_motor_stop();
    arm_motor_extend(1, 1);
    break;
    
    case FinalRetractArms:
    arm_motor_retract(1, 1);
    break;
    
    case SystemStop:
    track_motor_stop();
    arm_motor_stop(1, 1);
    break;
    
    default:
    //error
    break;
  }
  

  //next state logic
  switch (currentState) {
    case InitState:
    if(digitalRead(START_PIN) == HIGH){
      currentState = ExtendArms;
      DEBUG_PRINTSTATE("1ExtendArms");
    }
    break;
    
    case ExtendArms:
    if(digitalRead(RIGHT_ARM_EXTENDED) == HIGH){
      currentState = RetractArms;
      DEBUG_PRINTSTATE("RetractArms");
    }
    break;
    
    case RetractArms:
    if(digitalRead(RIGHT_ARM_RETRACTED) == HIGH){
      currentState = MoveForward;
      DEBUG_PRINTSTATE("MoveForward");
    }
    break;
    
    case MoveForward:
    track_motor_pos(left_pos, right_pos);
    if(!barrierCrossed && digitalRead(FRONT_BUMPER_LIMIT) == HIGH){
      currentState = BumpExtendArms;
      DEBUG_PRINTSTATE("BumpExtendArms");
    }
    else if(*right_pos - loopTics >= VehicleLength){
      currentState = ExtendArms;
      DEBUG_PRINTSTATE("2ExtendArms");
    }

    else if(barrierCrossed && digitalRead(FRONT_BUMPER_LIMIT) == HIGH){
      currentState = FinalExtendArms;
      DEBUG_PRINTSTATE("FinalExtendArms");
    }
    break;
    
    case BumpExtendArms:
    if(digitalRead(RIGHT_ARM_EXTENDED) == HIGH){
      currentState = BumpRetractArms;
      DEBUG_PRINTSTATE("BumpRetractArms");
    }
    break;
    
    case BumpRetractArms:
    if(digitalRead(RIGHT_ARM_RETRACTED) == HIGH){
      currentState = MoveOverBump;
      DEBUG_PRINTSTATE("MoveOverBump");
    }
    break;
    
    case MoveOverBump:
    track_motor_pos(left_pos, right_pos);
    if(*right_pos - loopTics >= VehicleLength + BumpLength){
      currentState = ExtendArms;
      DEBUG_PRINTSTATE("3ExtendArms");
    }
    break;
    
    case FinalExtendArms:
    if(digitalRead(RIGHT_ARM_EXTENDED) == HIGH){
      currentState = FinalRetractArms;
      DEBUG_PRINTSTATE("FinalRetractArms");
    }
    break;
    
    case FinalRetractArms:
    if(digitalRead(RIGHT_ARM_RETRACTED) == HIGH){
      currentState = SystemStop;
      DEBUG_PRINTSTATE("SystemStop");
    }
    break;
    
    case SystemStop:
    break;
    
    default:
    //error
    break;
  }
}

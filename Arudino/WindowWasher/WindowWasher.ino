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
//#define DEBUG

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

#define BumpLength 6
#define VehicleLength 12
#define WindowLength 72

enum State {InitState, ExtendArms, RetractArms, MoveForward, BumpExtendArms, 
            BumpRetractArms, MoveOverBump, FinalExtendArms, FinalRetractArms, SystemStop};
State currentState;
long loopTics;
long initialTics;

/*
 * For Demo on 3/21: Leds for motors, Micro Sevos, Limit Switches, Wire Encoder
 */

void setup() {
  DEBUG_START;
  currentState = InitState;
}

void loop() {
  switch (currentState) {
    case InitState:
    //initial Tics = tics
    break;
    
    case ExtendArms:
    //track motor off
    //arm motor on
    //loop Tics = tics
    break;
    
    case RetractArms:
    //arm motor on reverse
    break;
    
    case MoveForward:
    //arm motor off
    //track motor on
    //lower servo
    //lower tensioner
    break;
    
    case BumpExtendArms:
    //track motor off
    //arm motor on
    //loop Tics = tics
    break;
    
    case BumpRetractArms:
    //arm motor on reverse
    break;
    
    case MoveOverBump:
    //raise servo
    //raise tensioner
    //move forward
    break;
    
    case FinalExtendArms:
    //track motor off
    //arm motor on
    break;
    
    case FinalRetractArms:
    //arm motor on reverse
    break;
    
    case SystemStop:
    //track motor off
    //arm motor off
    break;
    
    default:
    //error
    break;
  }
  
  switch (currentState) {
    case InitState:
    DEBUG_PRINTSTATE("InitState");
    currentState = ExtendArms;
    DEBUG_PRINTSTATE("ExtendArms");
    break;
    
    case ExtendArms:
    //If Arm outer limit
    currentState = RetractArms;
    DEBUG_PRINTSTATE("RetractArms");
    break;
    
    case RetractArms:
    //If Arm inner limit
    currentState = MoveForward;
    DEBUG_PRINTSTATE("MoveForward");
    break;
    
    case MoveForward:
    //If Bump
    currentState = BumpExtendArms;
    DEBUG_PRINTSTATE("BumpExtendArms");

    //If tics - loopTics >= Vehicle Length
    currentState = ExtendArms;
    DEBUG_PRINTSTATE("ExtendArms");

    //If tics - loopTics >= Window Length
    currentState = FinalExtendArms;
    DEBUG_PRINTSTATE("FinalExtendArms");
    break;
    
    case BumpExtendArms:
    //If Arm outer limit
    currentState = BumpRetractArms;
    DEBUG_PRINTSTATE("BumpRetractArms");
    break;
    
    case BumpRetractArms:
    //If Arm inner limit
    currentState = MoveOverBump;
    DEBUG_PRINTSTATE("MoveOverBump");
    break;
    
    case MoveOverBump:
    //If tics - loopTics >= Vehicle Length + Bump Length
    currentState = ExtendArms;
    DEBUG_PRINTSTATE("ExtendArms");
    break;
    
    case FinalExtendArms:
    //If Arm outer limit
    currentState = FinalRetractArms;
    DEBUG_PRINTSTATE("FinalRetractArms");
    break;
    
    case FinalRetractArms:
    //If Arm inner limit
    currentState = SystemStop;
    DEBUG_PRINTSTATE("SystemStop");
    break;
    
    case SystemStop:
    break;
    
    default:
    //error
    break;
  }
}

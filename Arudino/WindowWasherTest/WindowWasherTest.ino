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


long currentState;
long loopTics;
long barrierCrossed;
/*
 * For Demo on 3/21: Leds for motors, Micro Sevos, Limit Switches, Wire Encoder
 */

int cntpwm;
int dirpwm;

void setup() {
  pinMode(RIGHT_ARM_EXTENDED, INPUT_PULLUP);
  pinMode(RIGHT_ARM_RETRACTED, INPUT_PULLUP);
  pinMode(FRONT_BUMPER_LIMIT, INPUT_PULLUP);
  DEBUG_START;

  cleaning_servos_setup();
  track_motor_setup();
  arm_motor_setup();
  track_motor_enable();


  cntpwm = 1;
  dirpwm = 1;
}

long leftPoslocal, rightPoslocal;

void loop() {
  track_motor_pos(&leftPoslocal, &rightPoslocal);
  //if(rightPoslocal < 5*270*16)
  track_motor_pid(2.88, 2.88);
  //else
  //track_motor_pid(0, 0);
  delay(50);
}

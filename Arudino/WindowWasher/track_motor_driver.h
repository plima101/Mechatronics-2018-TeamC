#include "pins.h"

//assigns pins and initializes 
void track_motor_setup(); 

void track_motor_enable();

void track_motor_stop();

//called in a consitent timing to make motors move at target velocity
void track_motor_pid(double left_target, double right_target);

//returns tic location of each motor
void track_motor_pos(long* left_pos, long* right_pos);



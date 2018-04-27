#include "pins.h"

//assigns pins and initializes variables 
void arm_motor_setup();

//if true, begins extension of side
void arm_motor_extend(bool left_extend, bool right_extend);

//if true, stops motor of side
void arm_motor_stop(bool left_stop, bool right_stop);

//if true, begin retraction of side
void arm_motor_retract(bool left_retract, bool right_retract);

void arm_run();

#include "accelerometer.h"
#include "MMA8451.h"

Adafruit_MMA8451 acc;
void accelerometer_setup(){
    acc.begin();
}

int accelerometer_read_x(){
    acc.read();
    return acc.x;
}

int accelerometer_read_y(){
    acc.read();
    return acc.y;
}
int accelerometer_read_z(){
    acc.read();
    return acc.z;
}

int accelerometer_read(int axis);


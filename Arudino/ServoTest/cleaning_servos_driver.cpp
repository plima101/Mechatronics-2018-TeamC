#include "cleaning_servos_driver.h"
#include "Arduino.h"
#include <Servo.h>

#define F_DOWN 60
#define F_UP 25
#define F_INIT 0
#define F_MID 40
#define B_DOWN 70
#define B_PUSH 80
#define B_UP 10

Servo front_servo;
Servo back_servo;
void cleaning_servos_setup(){
  back_servo.attach(RIGHT_SCRAPER);
  back_servo.write(B_UP);
  front_servo.attach(FRONT_SERVO);
  front_servo.write(F_INIT);
}

void cleaning_lift_front(){
  front_servo.write(F_UP); 
}
void cleaning_mid_front(){
  front_servo.write(F_MID);
}
void cleaning_lower_front(){
  front_servo.write(F_DOWN);
}

void lower_scrapers(){
  back_servo.write(B_DOWN);
}

void lift_scrapers(){
  back_servo.write(B_UP);
}

void push_scrapers(){
  back_servo.write(B_PUSH);
}
void test_front(long a){
  front_servo.write(a);
}
void test_back(long a){
  back_servo.write(a);
}


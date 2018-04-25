#include "cleaning_servos_driver.h"
#include "Arduino.h"
#include <Servo.h>

#define F_DOWN 30
#define F_UP 75
#define F_INIT 90
#define L_DOWN 95
#define L_UP 155
#define R_DOWN 65
#define R_UP 5 

Servo front_servo;
Servo left_scraper;
Servo right_scraper;
void cleaning_servos_setup(){
  front_servo.attach(FRONT_SERVO);
  front_servo.write(F_INIT);
  left_scraper.attach(LEFT_SCRAPER);
  left_scraper.write(L_UP);
  right_scraper.attach(RIGHT_SCRAPER);
  right_scraper.write(R_UP);
}

void cleaning_lift_front(){
  front_servo.write(F_UP); 
}

void cleaning_lower_front(){
  front_servo.write(F_DOWN);
}

void lower_scrapers(){
  left_scraper.write(L_DOWN);
  right_scraper.write(R_DOWN);
}

void lift_scrapers(){
  left_scraper.write(R_UP);
  right_scraper.write(L_UP);
}

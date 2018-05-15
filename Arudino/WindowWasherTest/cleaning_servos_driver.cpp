#include "cleaning_servos_driver.h"
#include "Arduino.h"
#include <Servo.h>

#define F_DOWN 80
#define F_UP 25
#define F_INIT 25
#define F_MID 40
#define B_DOWN 65
#define B_PUSH 90
#define B_UP 30 

#define L_U 170
#define L_S 60
#define R_U 60
#define R_S 170

Servo front_servo;
Servo back_servo;
Servo left_scraper;
Servo right_scraper;

void cleaning_servos_setup(){
  back_servo.attach(BACK_SERVO);
  back_servo.write(B_UP);
  front_servo.attach(FRONT_SERVO);
  front_servo.write(F_INIT);
  left_scraper.attach(LEFT_SCRAPER);
  left_scraper.write(L_U);
  right_scraper.attach(RIGHT_SCRAPER);
  right_scraper.write(R_U);
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

void actually_scrape(){
  left_scraper.write(L_S);
  right_scraper.write(R_S);
  delay(2000);
  left_scraper.write(L_U);
  right_scraper.write(R_U);
  delay(1000);
}



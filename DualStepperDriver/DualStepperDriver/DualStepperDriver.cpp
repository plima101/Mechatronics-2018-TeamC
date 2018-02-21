#include "DualStepperDriver.h"

DualStepperDriver::DualStepperDriver(int STEP1, int DIR1, int SLEEP1, 
                                     int STEP2, int DIR2, int SLEEP2){
    this->STEP1 = STEP1;
    this->STEP2 = STEP2;
    this->DIR1 = DIR1;
    this->DIR2 = DIR2;
    this->SLEEP1 = SLEEP1;
    this->SLEEP2 = SLEEP2;
    pinMode(STEP1, OUTPUT);
    pinMode(STEP2, OUTPUT);
    pinMode(DIR1, OUTPUT);
    pinMode(DIR2, OUTPUT);
    pinMode(SLEEP1, OUTPUT);
    pinMode(SLEEP2, OUTPUT);
}

void DualStepperDriver::Advance(int sC1, int sC2){
    while(sC1 > 0 || sC2 > 0){
        digitalWrite(this->STEP1, LOW);
        digitalWrite(this->STEP2, LOW);
        delay(4);
        if(sC1-- > 0) digitalWrite(this -> STEP1, HIGH);
        if(sC2-- > 0) digitalWrite(this -> STEP2, HIGH);
    }

}

void DualStepperDriver::Sleep(int s1, int s2){
    if(s1) digitalWrite(this->SLEEP1, LOW);
    if(s2) digitalWrite(this->SLEEP2, LOW);    
}
void DualStepperDriver::Wake(int w1, int w2){
    if(w1) digitalWrite(this->SLEEP1, HIGH);
    if(w2) digitalWrite(this->SLEEP2, HIGH); 
}
void DualStepperDriver::SetDirection(int d1, int d2){
    this->d1 = d1;
    this->d2 = d2;
    if(d1>0) digitalWrite(DIR1, HIGH);
    else digitalWrite(DIR1, LOW); 
    if(d2>0) digitalWrite(DIR2, HIGH);
    else digitalWrite(DIR2, LOW);
}
void DualStepperDriver::ChangeDirection(int c1, int c2){
    if(c1){
        if(d1 > 0){
            d1 = -1;
            digitalWrite(DIR1, LOW);
        }
        else{
            d1 = 1;
            digitalWrite(DIR1, HIGH);
        }
    }
    if(c2){
        if(d2 > 0){
            d2 = -1;
            digitalWrite(DIR2, LOW);
        }
        else{
            d2 = 1;
            digitalWrite(DIR2, HIGH);
        }
    }
}

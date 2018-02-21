#define PIN_STEP1 3
#define PIN_DIR1 4
#define PIN_SLEEP1 5
#define PIN_STEP2 6
#define PIN_DIR2 7
#define PIN_SLEEP2 8
#include "DualStepperDriver.h"
#include "MMA8451.h"

DualStepperDriver s = DualStepperDriver(PIN_STEP1, PIN_DIR1, PIN_SLEEP1, PIN_STEP2, PIN_DIR2, PIN_SLEEP2);
Adafruit_MMA8451 mma = Adafruit_MMA8451();
void setup() {
  s.SetDirection(1, -1);
  s.Wake(1,1); 
  Serial.begin(9600);
  Serial.println("MMA8451 Testing!");

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found");
}

void loop() {
  while(1){
    mma.read();
    int lA = 10 - (int)mma.y_ms2;
    int rA = 10 + (int)mma.y_ms2;
    Serial.println(lA);
    Serial.println(rA);
    s.Advance(lA, rA);
  }
}

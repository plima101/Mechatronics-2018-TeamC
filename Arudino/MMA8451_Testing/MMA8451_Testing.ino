#include "MMA8451.h"

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup() {
  Serial.begin(9600);
  Serial.println("MMA8451 Testing!");

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
}

void loop() {
  unsigned long startTime = micros();
  mma.read();
  Serial.print("Read Time: "); Serial.print(micros() - startTime); Serial.println(" us");
  Serial.println();
  
  Serial.print("X:\t"); Serial.print(mma.x); 
  Serial.print("\tY:\t"); Serial.print(mma.y); 
  Serial.print("\tZ:\t"); Serial.print(mma.z); 
  Serial.println();

  Serial.print("X:\t"); Serial.print(mma.x_ms2); 
  Serial.print("\tY:\t"); Serial.print(mma.y_ms2); 
  Serial.print("\tZ:\t"); Serial.print(mma.z_ms2); 
  Serial.println("m/s^2 ");
  Serial.println();

  unsigned long delayTime = micros();
  delay(500);
  Serial.print("Delay Time: "); Serial.print(micros() - delayTime); Serial.println(" us");
  Serial.print("Total Time: "); Serial.print(micros() - startTime); Serial.println(" us");
  Serial.println();
}

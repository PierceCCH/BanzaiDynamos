#include "gyroscope.h"

MPU6050 mpu(Wire); // -- Gyroscope

void setupGyroscope(){
    Serial.begin(9600);
    Wire.begin();
    byte status = mpu.begin();
    Serial.println(status);
    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    mpu.calcOffsets();
}

int getYaw(){
  mpu.update();
  return mpu.getAngleZ();
}
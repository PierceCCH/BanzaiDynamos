#ifndef _GYROSCOPE_H
#define _GYROSCOPE_H

#include "Wire.h"
#include <MPU6050_light.h>

void setupGyroscope();
int getYaw();

#endif
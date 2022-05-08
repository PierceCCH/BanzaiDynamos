#ifndef _ULTRASONIC_SENSOR_H
#define _ULTRASONIC_SENSOR_H

#include <Arduino.h>

void setupUltrasonicSensors();
int getDistanceFromSensor(int trigPin, int echoPin);

#endif
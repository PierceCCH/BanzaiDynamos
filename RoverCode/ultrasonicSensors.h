#ifndef _ULTRASONIC_SENSOR_H
#define _ULTRASONIC_SENSOR_H

#include <Arduino.h>

constexpr int kEchoB = 22;
constexpr int kTrigB = 23;
constexpr int kEchoFM = 24;
constexpr int kTrigFM = 25;
constexpr int kEchoFR = 26;
constexpr int kTrigFR = 27;
constexpr int kEchoL = 28;
constexpr int kTrigL = 29;
constexpr int kEchoR = 30;
constexpr int kTrigR = 31;
constexpr int kEchoFL = 32;
constexpr int kTrigFL = 33;

void setupUltrasonicSensors();
int getDistanceFromSensor(int trigPin, int echoPin);

#endif

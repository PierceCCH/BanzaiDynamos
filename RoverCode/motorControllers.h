#ifndef _MOTOR_CONTROLLERS_H
#define _MOTOR_CONTROLLERS_H
#include <Arduino.h>

void setupMotors();
void enableMove();
void stopMove();
void frontRightForward();
void frontRightBackwards();
void frontLeftForward();
void frontLeftBackwards();
void backRightForward();
void backRightBackwards();
void backLeftForward();
void backLeftBackwards();
void moveForward();
void moveBackward();
void strafeLeft();
void strafeRight();
void rotate(int angle);

#endif
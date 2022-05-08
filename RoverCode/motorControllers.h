#ifndef _MOTOR_CONTROLLERS_H
#define _MOTOR_CONTROLLERS_H
#include <Arduino.h>

void setupMotors();

// Starts / Stops all rovers
void enableMove();
void stopMove();

// Individual Motor Controllers
void frontRightForward();
void frontRightBackwards();
void frontLeftForward();
void frontLeftBackwards();
void backRightForward();
void backRightBackwards();
void backLeftForward();
void backLeftBackwards();

// Generic rover movement
void moveForward();
void moveBackward();
void strafeLeft();
void strafeRight();
void rotate(int angle);

void calculatePID();

#endif

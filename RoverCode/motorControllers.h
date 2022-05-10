#ifndef _MOTOR_CONTROLLERS_H
#define _MOTOR_CONTROLLERS_H
#include <Arduino.h>

void setupMotors();

// Stops all motors
void stopMove();

// Individual Motor Controllers


void setFrontLeft(int speed);
void setFrontRight(int speed);
void setBackLeft(int speed);
void setBackRight(int speed);

// Generic rover movement
void moveForward();
void moveBackward();
void strafeLeft();
void strafeRight();
void rotate(int angle);

void calculatePID();

#endif

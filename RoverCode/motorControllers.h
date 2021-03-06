#ifndef _MOTOR_CONTROLLERS_H
#define _MOTOR_CONTROLLERS_H
#include <Arduino.h>

// -------------- DEFINE PINS --------------
const int BackRightF = 11;
const int BackRightB = 10;
const int FrontLeftF = 9;
const int FrontLeftB = 8;
const int BackLeftF = 7;
const int BackLeftB = 6;
const int FrontRightF = 5;
const int FrontRightB = 4;
// RIGHT H-Bridge pins
const int ENAright = A1; // Enables motor 
const int ENBright = A2;
// LEFT H-Bridge 
const int ENAleft = A3;
const int ENBleft = A4;

void setupMotors();

// Stops all motors
void stopMove();
void testMotor();

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
void rotate(int angle, int del);

void calculatePID();

#endif

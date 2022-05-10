#ifndef _MOTOR_CONTROLLERS_H
#define _MOTOR_CONTROLLERS_H
#include <Arduino.h>

// -------------- DEFINE PINS --------------
const int FrontRightF = 13;
const int FrontRightB = 12;
const int BackRightF = 11;
const int BackRightB = 10;
const int FrontLeftF = 9;
const int FrontLeftB = 8;
const int BackLeftF = 7;
const int BackLeftB = 6;
// RIGHT H-Bridge pins
const int ENAright = A0; // Enables motor 
const int ENBright = A1;
// LEFT H-Bridge 
const int ENAleft = A2;
const int ENBleft = A3;

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

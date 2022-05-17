#ifndef _MOTOR_CONTROLLERS_H
#define _MOTOR_CONTROLLERS_H
#include <Arduino.h>

// -------------- DEFINE PINS --------------
const int FrontRightF = 43;
const int FrontRightB = 42;
const int BackRightF = 41;
const int BackRightB = 40;
const int FrontLeftF = 39;
const int FrontLeftB = 38;
const int BackLeftF = 37;
const int BackLeftB = 36;
// RIGHT H-Bridge pins
const int ENAright = A0; // Enables motor 
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
void rotate(int angle);

void calculatePID();

#endif

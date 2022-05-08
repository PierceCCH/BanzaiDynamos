#include "motorControllers.h"
#include "gyroscope.h"

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

void setupMotors(){
    for (int i = BackLeftB; i <= FrontRightF; i++){
        pinMode(i, OUTPUT);
    }
    pinMode (ENAright, OUTPUT);
    pinMode (ENBright, OUTPUT);
    pinMode (ENAleft, OUTPUT);
    pinMode (ENBleft, OUTPUT);
}

// ------ WHEEL MOTOR CONTROLLERS ------
void enableMove(){
//control speed 
  analogWrite(ENAleft, 255);
  analogWrite(ENBleft, 255); 
  analogWrite(ENAright, 255);
  analogWrite(ENBright, 255); 
}

void stopMove(){
  analogWrite(ENAleft, 0);
  analogWrite(ENBleft, 0); 
  analogWrite(ENAright, 0);
  analogWrite(ENBright, 0); 
}

void frontRightForward(){
  digitalWrite(FrontRightF, HIGH);
  digitalWrite(FrontRightB, LOW);
}

void frontRightBackwards(){
  digitalWrite(FrontRightF, LOW);
  digitalWrite(FrontRightB, HIGH);
}

void frontLeftForward(){
  digitalWrite(FrontLeftF, HIGH);
  digitalWrite(FrontLeftB, LOW);
}

void frontLeftBackwards(){
  digitalWrite(FrontLeftF, LOW);
  digitalWrite(FrontLeftB, HIGH);
}

void backRightForward(){
  digitalWrite(BackRightF, HIGH);
  digitalWrite(BackRightB, LOW);
}

void backRightBackwards(){
  digitalWrite(BackRightF, LOW);
  digitalWrite(BackRightB, HIGH);
}

void backLeftForward(){
  digitalWrite(BackLeftF, HIGH);
  digitalWrite(BackLeftB, LOW);
}

void backLeftBackwards(){
  digitalWrite(BackLeftF, LOW);
  digitalWrite(BackLeftB, HIGH);
}
/*----------------------------------
  FL -> FORWARDS | FR -> FORWARDS
                  |
  BL -> FORWARDS  | BR -> FORWARDS
----------------------------------*/
void moveForward(){
  enableMove();
  frontRightForward();
  frontLeftForward();
  backLeftForward();
  backRightForward();
}

/*----------------------------------
  FL -> BACKWARDS | FR -> BACKWARDS
                  |
  BL -> BACKWARDS | BR -> BACKWARDS
----------------------------------*/
void moveBackward(){
  enableMove();
  frontLeftBackwards();
  frontRightBackwards();
  backLeftBackwards();
  backRightBackwards();
}

/*----------------------------------
  FL -> BACKWARDS | FR -> FORWARDS
                  |
  BL -> FORWARDS  | BR -> BACKWARDS
----------------------------------*/
void strafeLeft(){
  enableMove();
  frontLeftBackwards();
  frontRightForward();
  backLeftBackwards();
  backLeftForward();
}

/*----------------------------------
  FL -> FORWARDS  | FR -> BACKWARDS
                  |
  BL -> BACKWARDS | BR -> FORWARDS
----------------------------------*/
void strafeRight(){
  enableMove();
  frontLeftForward();
  frontRightBackwards();
  backLeftBackwards();
  backRightForward();
}

void rotate(int angle){
  /*
    Angle POSITIVE for ACW rotation, negative for CW rotation
  */
  int currentAngle = getYaw();
  int finalAngle = currentAngle + angle;
  
  while (abs(currentAngle) < abs(finalAngle - 1)){ // Allow for a certain threshold
    if (angle < 0){ // ACW rotation
      enableMove();
      frontRightForward();
      frontLeftBackwards();
      backRightForward();
      backLeftBackwards();
      delay(10); // time spent rotating
      stopMove();
    } else { // CW rotation
      enableMove();
      frontRightBackwards();
      frontLeftForward();
      backRightBackwards();
      backLeftForward();
      delay(10);
      stopMove();
    }
    currentAngle = getYaw();
    Serial.println(currentAngle);
    Serial.println(finalAngle);
  }
}

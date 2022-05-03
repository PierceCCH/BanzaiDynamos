// --------------- LIBRARIES ---------------
#include "Wire.h"
#include <MPU6050_light.h>
// -------------- DEFINE PINS -------------- 
// ---------- MOTORS ----------
// -- RIGHT SIDE
// FRONT RIGHT MOTOR
const int FrontRightF = 13;
const int FrontRightB = 12;
// BACK RIGHT MOTOR
const int BackRightF = 11;
const int BackRightB = 10;
// RIGHT H-Bridge pins
const int ENAright = A0; // Enables motor 
const int ENBright = A1;
// -- LEFT SIDE
// FRONT LEFT MOTOR
const int FrontLeftF = 9;
const int FrontLeftB = 8;
// BACK LEFT MOTOR
const int BackLeftF = 7;
const int BackLeftB = 6;
// LEFT H-Bridge 
const int ENAleft = A2;
const int ENBleft = A3;
// ------------------------------------
// -------- VARIABLES ---------
MPU6050 mpu(Wire); // Gyroscope
unsigned long timer = 0;

void setup() {
// -- Motor pin setup --
  pinMode (FrontRightF, OUTPUT);
  pinMode (FrontRightB, OUTPUT);
  pinMode (BackRightB, OUTPUT);
  pinMode (BackRightF, OUTPUT);
  pinMode (ENAright, OUTPUT);
  pinMode (ENBright, OUTPUT);
  pinMode (FrontLeftF, OUTPUT);
  pinMode (FrontLeftB, OUTPUT);
  pinMode (BackLeftB, OUTPUT);
  pinMode (BackLeftF, OUTPUT);
  pinMode (ENAleft, OUTPUT);
  pinMode (ENBleft, OUTPUT);

// -- Gyroscope setup --
  Serial.begin(9600);
  Wire.begin();
  byte status = mpu.begin();
  Serial.println(status);
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();
}

void loop() {
  delay(500);
  moveForward();
  delay(1500);
  moveBackward();
  delay(500);
  strafeLeft();
  delay(1500);
  strafeRight();
  delay(500);
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
void strafeRight(){
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
void strafeLeft(){
  enableMove();
  frontLeftForward();
  frontRightBackwards();
  backLeftBackwards();
  backRightForward();
}

int getYaw(){
  return mpu.getAngleZ();
}

void rotate(int angle){
  /*
    Angle POSITIVE for ACW rotation, negative for CW rotation
  */
  int currentAngle = getYaw();
  int finalAngle = currentAngle + angle;
  while (currentAngle != finalAngle){
    if (angle < 0){ // CW rotation
      enableMove();
      frontRightForward();
      frontLeftBackwards();
      backRightForward();
      backLeftBackwards();
      delay(50);
      stopMove();
    } else {
      enableMove();
      frontRightForward();
      frontLeftForward();
      backRightBackwards();
      backLeftForward();
      delay(50);
      stopMove();
    }
    delay(50);
    currentAngle = getYaw();
  }
}

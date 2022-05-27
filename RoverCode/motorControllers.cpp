#include "motorControllers.h"
#include "gyroscope.h"

void setupMotors(){
    for (int i = FrontRightB; i <= BackRightF; i++){
        pinMode(i, OUTPUT);
    }
    pinMode (ENAright, OUTPUT);
    pinMode (ENBright, OUTPUT);
    pinMode (ENAleft, OUTPUT);
    pinMode (ENBleft, OUTPUT);
}

void stopMove(){
  analogWrite(ENAleft, 0);
  analogWrite(ENBleft, 0); 
  analogWrite(ENAright, 0);
  analogWrite(ENBright, 0); 
}

void setFrontRight(int speed){
  if( speed==0 ) {
    digitalWrite( FrontRightF, LOW );
    digitalWrite( FrontRightB, LOW );
    analogWrite(ENAright, 0);    
  } else if( speed>0 ) {
    analogWrite( FrontRightF, speed );
    digitalWrite( FrontRightB, LOW );
    analogWrite ( ENAright, speed);        
  } else {
    digitalWrite( FrontRightF, LOW );
    analogWrite( FrontRightB, -speed );
    analogWrite ( ENAright, -speed);            
  }
}
void setBackRight(int speed){
  if( speed==0 ) {
    digitalWrite( BackRightF, LOW );
    digitalWrite( BackRightB, LOW );
    analogWrite(ENBright, 0);    
  } else if( speed>0 ) {
    analogWrite( BackRightF, speed );
    digitalWrite( BackRightB, LOW );
    analogWrite ( ENBright, speed);        
  } else {
    digitalWrite( BackRightF, 0 );
    analogWrite( BackRightB, -speed );
    analogWrite ( ENBright, -speed);            
  }
}
void setFrontLeft(int speed){
  if( speed==0 ) {
    digitalWrite( FrontLeftF, LOW );
    digitalWrite( FrontLeftB, LOW );
    analogWrite(ENAleft, 0);    
  } else if( speed>0 ) {
    analogWrite( FrontLeftF, speed );
    digitalWrite( FrontLeftB, LOW );
    analogWrite ( ENAleft, speed);        
  } else {
    digitalWrite( FrontLeftF, LOW );
    analogWrite( FrontLeftB, -speed );
    analogWrite ( ENAleft, -speed);            
  }
}
void setBackLeft(int speed){
  if( speed==0 ) {
    digitalWrite( BackLeftF, LOW );
    digitalWrite( BackLeftB, LOW );
    analogWrite(ENBleft, 0);    
  } else if( speed>0 ) {
    analogWrite( BackLeftF, speed );
    digitalWrite( BackLeftB, LOW );
    analogWrite ( ENBleft, speed);        
  } else {
    digitalWrite( BackLeftF, LOW );
    analogWrite( BackLeftB, -speed );
    analogWrite ( ENBleft, -speed);            
  }
}

/*----------------------------------
  FL -> FORWARDS | FR -> FORWARDS
                  |
  BL -> FORWARDS  | BR -> FORWARDS
----------------------------------*/
void moveForward(){
  setFrontRight(0);
  setBackRight(255);
  setFrontLeft(0);
  setBackLeft(0);
}

/*----------------------------------
  FL -> BACKWARDS | FR -> BACKWARDS
                  |
  BL -> BACKWARDS | BR -> BACKWARDS
----------------------------------*/
void moveBackward(){
  setFrontRight(-255);
  setBackRight(-255);
  setFrontLeft(-255);
  setBackLeft(-255);
}

/*----------------------------------
  FL -> BACKWARDS | FR -> FORWARDS
                  |
  BL -> FORWARDS  | BR -> BACKWARDS
----------------------------------*/
void strafeLeft(){
  setFrontRight(255);
  setBackRight(-255);
  setFrontLeft(-255);
  setBackLeft(255);
}

/*----------------------------------
  FL -> FORWARDS  | FR -> BACKWARDS
                  |
  BL -> BACKWARDS | BR -> FORWARDS
----------------------------------*/
void strafeRight(){
  setFrontRight(-255);
  setBackRight(255);
  setFrontLeft(255);
  setBackLeft(-255);
}

/*
  Rotates rover 90 degrees.
  dir POSITIVE for CW rotation, negative for ACW rotation.
*/
void rotate(int dir){
  if (dir < 0){ // ACW rotation
    setFrontRight(255);
    setBackLeft(-255);
    setBackRight(255);
    setFrontLeft(-255);
    delay(250); // time spent rotating in ms
  } else { // CW rotation
    setFrontRight(-255);
    setBackLeft(255);
    setBackRight(-255);
    setFrontLeft(255);      
    delay(250);
  }
}

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
    analogWrite(ENAright, 0);    
  } else if( speed>0 ) {
    digitalWrite( FrontRightF, HIGH );
    digitalWrite( FrontRightB, LOW );
    analogWrite ( ENAright, speed);        
  } else {
    digitalWrite( FrontRightF, LOW );
    digitalWrite( FrontRightB, HIGH );
    analogWrite ( ENAright, -speed);            
  }
}
void setBackRight(int speed){
  if( speed==0 ) {
    analogWrite(ENBright, 0);    
  } else if( speed>0 ) {
    digitalWrite( BackRightF, HIGH );
    digitalWrite( BackRightB, LOW );
    analogWrite ( ENBright, speed);        
  } else {
    digitalWrite( BackRightF, LOW );
    digitalWrite( BackRightB, HIGH );
    analogWrite ( ENBright, -speed);            
  }
}
void setFrontLeft(int speed){
  if( speed==0 ) {
    analogWrite(ENAleft, 0);    
  } else if( speed>0 ) {
    digitalWrite( FrontLeftF, HIGH );
    digitalWrite( FrontLeftB, LOW );
    analogWrite ( ENAleft, speed);        
  } else {
    digitalWrite( FrontLeftF, LOW );
    digitalWrite( FrontLeftB, HIGH );
    analogWrite ( ENAleft, -speed);            
  }
}
void setBackLeft(int speed){
  if( speed==0 ) {
    analogWrite(ENBleft, 0);    
  } else if( speed>0 ) {
    digitalWrite( BackLeftF, HIGH );
    digitalWrite( BackLeftB, LOW );
    analogWrite ( ENBleft, speed);        
  } else {
    digitalWrite( BackLeftF, LOW );
    digitalWrite( BackLeftB, HIGH );
    analogWrite ( ENBleft, -speed);            
  }
}

/*----------------------------------
  FL -> FORWARDS | FR -> FORWARDS
                  |
  BL -> FORWARDS  | BR -> FORWARDS
----------------------------------*/
void moveForward(){
  setFrontRight(150);
  setBackRight(255);
  setFrontLeft(150);
  setBackLeft(150);
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
  Rotates rover
  dir POSITIVE for CW rotation, negative for ACW rotation.
*/
void rotate(int dir, int del){
  if (dir < 0){ // ACW rotation
    setFrontRight(255);
    setBackLeft(-255);
    setBackRight(255);
    setFrontLeft(-255);
    delay(del); // time spent rotating in ms
  } else { // CW rotation
    setFrontRight(-255);
    setBackLeft(255);
    setBackRight(-255);
    setFrontLeft(255);      
    delay(del);
  }
  stopMove();
}

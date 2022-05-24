#include "motorControllers.h"
#include "gyroscope.h"

void setupMotors(){
    for (int i = BackLeftB; i <= FrontRightF; i++){
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

void testMotor(){
    digitalWrite( FrontLeftF, HIGH);
    digitalWrite( FrontLeftB, LOW);
    analogWrite(ENAleft, 255);
    analogWrite(ENBleft, 255);
}

void setFrontRight(int speed){
  if( speed==0 ) {
    digitalWrite( FrontRightF, HIGH );
    digitalWrite( FrontRightB, HIGH );
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
    digitalWrite( BackRightF, HIGH );
    digitalWrite( BackRightB, HIGH );
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
    digitalWrite( FrontLeftF, HIGH );
    digitalWrite( FrontLeftB, HIGH );
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
    digitalWrite( BackLeftF, HIGH );
    digitalWrite( BackLeftB, HIGH );
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
  setFrontRight(255);
  setBackRight(255);
  setFrontLeft(255);
  setBackLeft(255);
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

void rotate(int angle){
  /*
    Angle POSITIVE for ACW rotation, negative for CW rotation
  */
  int currentAngle = getYaw();
  int finalAngle = currentAngle + angle;
  
  while (abs(currentAngle) < abs(finalAngle - 1)){ // Allow for a certain threshold
    if (angle < 0){ // ACW rotation
      setFrontRight(255);
      setBackLeft(-255);
      setBackRight(255);
      setFrontLeft(-255);
      delay(10); // time spent rotating
      stopMove();
    } else { // CW rotation
      setFrontRight(-255);
      setBackLeft(255);
      setBackRight(-255);
      setFrontLeft(255);      
      delay(10);
      stopMove();
    }
    currentAngle = getYaw();
    Serial.println(currentAngle);
    Serial.println(finalAngle);
  }
}

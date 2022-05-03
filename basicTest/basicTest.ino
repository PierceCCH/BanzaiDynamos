// --------------- LIBRARIES ---------------
#include "Wire.h"
#include <Servo.h>
#include <MPU6050_light.h>

// -------------- DEFINE PINS -------------- 
// ---------- MOTORS ----------
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

// ------ ULTRASONIC SENSORS ------
const int EchoFrontLeft = 22;
const int TrigFrontLeft = 23;
const int EchoFrontMid = 24;
const int TrigFrontMid = 25;
const int EchoFrontRight = 26;
const int TrigFrontRight = 27;
const int EchoLeft = 28;
const int TrigLeft = 29;
const int EchoRight = 30;
const int TrigRight = 31;
const int EchoBack = 32;
const int TrigBack = 33;

// -------- CLAW SERVO --------
const int ClawServo = 3;

// ------------------------------------
// -------- VARIABLES ---------
MPU6050 mpu(Wire); // -- Gyroscope
Servo claw;

void setup() {
// -- Motor pin setup --
  for (int i = BackLeftB; i <= FrontRightF; i++){
    pinMode(i, OUTPUT);
  }
  pinMode (ENAright, OUTPUT);
  pinMode (ENBright, OUTPUT);
  pinMode (ENAleft, OUTPUT);
  pinMode (ENBleft, OUTPUT);

// -- Ultrasonic sensor setup ----
  for (int i = EchoFrontLeft; i <= TrigBack; i++){
    if (i%2 == 0){ // ECHO PINS MUST BE EVEN PINS
      pinMode(i, INPUT);
    } else { // TRIG PINS MUST BE ODD PINS
      pinMode(i, OUTPUT);
    }
  }

// -- Gyroscope setup --
  Serial.begin(9600);
  Wire.begin();
  byte status = mpu.begin();
  Serial.println(status);
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();

// -- Servo setup --
  claw.attach(ClawServo);
}

void loop() {
  motorTestSequence();
  stopMove();
  openClaw();
  closeClaw();
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
  while (currentAngle > (finalAngle - 1) || currentAngle < (finalAngle + 1)){ // Allow for a certain threshold
    if (angle < 0){ // CW rotation
      enableMove();
      frontRightForward();
      frontLeftBackwards();
      backRightForward();
      backLeftBackwards();
      delay(50); // time spent rotating
      stopMove();
    } else {
      enableMove();
      frontRightBackwards();
      frontLeftForward();
      backRightBackwards();
      backLeftForward();
      delay(50);
      stopMove();
    }
    currentAngle = getYaw();
  }
}

// ------ Ultrasonic Sensor Controller ------
int getDistanceFromSensor(int trigPin, int echoPin){
  // Clear trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads echo and uses return time to calculate the distance
  int distance = pulseIn(echoPin, HIGH) * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

// ------ Claw Controller ------
void openClaw(){
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    claw.write(pos);   // tell servo to go to position 'pos'
    delay(15);  // waits 15ms for the servo to reach the position
  }
}
void closeClaw(){
    for (pos = 0; pos <= 180; pos -= 1) {
    // in steps of 1 degree
    claw.write(pos);
    delay(15); 
}

void motorTestSequence(){
  delay(500);
  moveForward();
  delay(1000);
  stopMove();
  moveBackward();
  delay(1000);
  stopMove();
  strafeLeft();
  delay(1000);
  stopMove();
  strafeRight();
  delay(1000);

  rotate(180);
  delay(500);
  rotate(180);
  delay(500);
  rotate(-180);
  delay(500);
  rotate(-180);
  delay(500);
}
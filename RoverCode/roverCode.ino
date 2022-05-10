#include "motorControllers.h"
#include "ultrasonicSensors.h"
#include "clawController.h"
#include "gyroscope.h"

void setup(){
    setupMotors();
    setupUltrasonicSensors();
    setupClaw();
    setupGyroscope();
}

void loop(){
    delay(100);
    moveForward();
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

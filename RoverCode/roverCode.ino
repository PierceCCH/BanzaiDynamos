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

}
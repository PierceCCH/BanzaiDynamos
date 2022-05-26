#include "clawController.h"
#include <Servo.h>

Servo claw;

void setupClaw(){
    // -- Servo setup --
    claw.attach(ClawServo);
    claw.write(100); // Start with claw fully open
}

void openClaw(){
    claw.write(100);
}
void closeClaw(){
    claw.write(0);
}

#include "clawController.h"
#include <Servo.h>

Servo claw;

void setupClaw(){
    // -- Servo setup --
    claw.attach(ClawServo);
}

void openClaw(){
    for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    claw.write(pos);   // tell servo to go to position 'pos'
    delay(15);  // waits 15ms for the servo to reach the position
  }
}
void closeClaw(){
    for (int pos = 180; pos >= 0; pos -= 1) {
    // in steps of 1 degree
    claw.write(pos);
    delay(15);
   }
}
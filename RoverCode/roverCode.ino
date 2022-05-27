#include "motorControllers.h"
#include "ultrasonicSensors.h"
#include "clawController.h"

constexpr int kObstacleThresh = 10; // for frontal sensors
constexpr int kCollWallThresh = 15; // for side sensors
constexpr int kZoneWallThresh = 300;
constexpr int kTargetThresh = 10; // Change to length of right part of zone

constexpr double kZoneX = 10; // X coordinate of drop zone in cm
constexpr double kZoneY = 10; // Y coordinate of drop zone in cm

constexpr double speedX = 10; // front back speed of rover in cm/s
constexpr double speedY = 10; // strafe speed of rover in cm/s

int state = 1;
bool final_zone = false;

void setup(){
    Serial.begin(9600);
    setupMotors();
    setupUltrasonicSensors();
    setupClaw();
}

void loop(){
  
    Serial.print("FR ");
    Serial.println(getDistanceFromSensor(kTrigFR, kEchoFR));
    Serial.print("FM ");
    Serial.println(getDistanceFromSensor(kTrigFM, kEchoFM));
    Serial.print("FL ");
    Serial.println(getDistanceFromSensor(kTrigFL, kEchoFL));
    Serial.print("L ");
    Serial.println(getDistanceFromSensor(kTrigL, kEchoL));
    Serial.print("R ");
    Serial.println(getDistanceFromSensor(kTrigR, kEchoR));
    Serial.print("B ");
    Serial.println(getDistanceFromSensor(kTrigB, kEchoB));
    moveForward();
  
/*
    if (state == 0) { // Navigate obstacles
        int obstacle_FL = getDistanceFromSensor(kTrigFL, kEchoFL);
        int obstacle_FR = getDistanceFromSensor(kTrigFR, kEchoFR);

        if (obstacle_FL < kObstacleThresh || obstacle_FR < kObstacleThresh) {
            stopMove();
            avoidObstacle();
            moveForward();
        }
        else {
            moveForward();
            int wall_L = getDistanceFromSensor(kTrigL, kEchoL);
            int wall_R = getDistanceFromSensor(kTrigR, kEchoR);
            
            if ((wall_L + wall_R) > kZoneWallThresh) {
                moveForward();
                delay(100);
                stopMove();
                ++state;
                delay(1000);
            }
        }
    } else if (state == 1) { // Find target
        if (!final_zone) {
            rotate(1); // Rotate CW
            final_zone = true;
        }
        int obstacle_L = getDistanceFromSensor(kTrigL, kEchoL);
        int obstacle_Front = getDistanceFromSensor(kTrigFM, kEchoFM);
 
        if (obstacle_Front < kTargetThresh){ // Spotted target
            while (obstacle_Front > kObstacleThresh){ // Move forward towards target if no obstacles
                obstacle_Front = getDistanceFromSensor(kTrigFM, kEchoFM);
                moveForward();
            }
            stopMove();
            Serial.print("Close claw");
            closeClaw();
            ++state;
        } else {
            if (obstacle_L > kCollWallThresh){ // Strafe left to scan for target
                strafeLeft();
                obstacle_L = getDistanceFromSensor(kTrigL, kEchoL);
            }
        }
    } else if (state == 2) { // Transport target
        int obstacle_L = getDistanceFromSensor(kTrigL, kEchoL);
        int wall_B = getDistanceFromSensor(kTrigB, kEchoB);
 
        while (obstacle_L > kCollWallThresh){ // Strafe left till aligned with wall
            strafeRight();
            obstacle_L = getDistanceFromSensor(kTrigL, kEchoL);
        }
        while (wall_B < kCollWallThresh){ // move forward till reach top right corner
            moveBackward();
            wall_B = getDistanceFromSensor(kTrigB, kEchoB);
        }
        stopMove();
        
        // Move to drop zone
        moveForward();
        delay( ( kZoneX / speedX ) * 1000);
        strafeRight();
        delay( ( kZoneY / speedY ) * 1000);

        delay(500); // Drop cylinder
        openClaw();

        moveBackward();
        delay(500);

        ++state;
    } else if (state == 3) { // Finish execution
        return;
    } else {
      Serial.print("invalid state: ");
      Serial.println(state);
      return;
    }*/
}

void avoidObstacle() {
    int obstacle_FL = getDistanceFromSensor(kTrigFL, kEchoFL);
    int obstacle_FM = getDistanceFromSensor(kTrigFM, kEchoFM);
    int obstacle_FR = getDistanceFromSensor(kTrigFR, kEchoFR);
    if (obstacle_FL < kObstacleThresh || obstacle_FL < kObstacleThresh) {
        if (obstacle_FR < kObstacleThresh) {
            int random_dir = random(0, 2);
            if (random_dir == 0) {
                strafeLeft();
            } else {
                strafeRight();
            }
            
            int wall_L;
            int wall_R;
            for (;;) {
                obstacle_FL = getDistanceFromSensor(kTrigFL, kEchoFL);
                obstacle_FM = getDistanceFromSensor(kTrigFM, kEchoFM);
                obstacle_FR = getDistanceFromSensor(kTrigFR, kEchoFR);
                wall_L = getDistanceFromSensor(kTrigL, kEchoL);
                wall_R = getDistanceFromSensor(kTrigR, kEchoR);
                if (!(obstacle_FL < kObstacleThresh ||
                      obstacle_FM < kObstacleThresh ||
                      obstacle_FR < kObstacleThresh)) {
                    stopMove();
                    return;
                }
                else if (wall_L < kCollWallThresh) {
                    stopMove();
                    strafeRight();
                }
                else if (wall_R < kCollWallThresh) {
                    stopMove();
                    strafeLeft();
                }
            }
        } else {
            strafeRight();
            for (;;) {
                obstacle_FL = getDistanceFromSensor(kTrigFL, kEchoFL);
                if (!(obstacle_FL < kObstacleThresh)) {
                    stopMove();
                    return;
                }
            }
        }
    } else {
        if (obstacle_FR < kObstacleThresh) {
            strafeLeft();
            for (;;) {
                obstacle_FR = getDistanceFromSensor(kTrigFR, kEchoFR);
                if (!(obstacle_FR < kObstacleThresh)) {
                    stopMove();
                    return;
                }
            }
        }
        else {
            return;
        }
    }
}

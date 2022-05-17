#include "motorControllers.h"
#include "ultrasonicSensors.h"
#include "clawController.h"
#include "gyroscope.h"

constexpr int kObstacleThresh = 2;
constexpr int kCollWallThresh = 10;
constexpr int kZoneWallThresh = 2000; //TODO
constexpr int kTargetThresh = 5; // TODO
constexpr int kOriginThresh = 10;

constexpr int kZoneX = 10; 
constexpr int kZoneY = 10;

int state;

void setup(){
    setupMotors();
    setupUltrasonicSensors();
    setupClaw();
//    setupGyroscope();
    
    state = 0;
}

void loop(){
  /*
    moveForward();
    delay(5000);
    moveBackward();
    delay(5000);
    strafeLeft();
    delay(5000);
    strafeRight();
    delay(5000);
    */
    switch(state) {
      case 0: // Navigate obstacles
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
                delay(5);
                stopMove();
                ++state;
            }
        }
        break;
      case 1: // Find target
        rotate(-90); // Rotate right
        int obstacle_L = getDistanceFromSensor(kTrigL, kEchoL);
        int obstacle_Front = getDistanceFromSensor(kTrigFM, kEchoFM);
 
        if (obstacle_Front < kTargetThresh){
            while (obstacle_Front > kObstacleThresh){
                moveForward();
            }
            stopMove();
            openClaw();
            closeClaw();
            state++;
        } else if (obstacle_L > kCollWallThresh){
            strafeLeft();
        }
        break;
      case 2: // Transport target
        rotate(180);
        int obstacle_R = getDistanceFromSensor(kTrigR, kEchoR);
        int wall_FL = getDistanceFromSensor(kTrigFL, kEchoFL);
        int wall_FR = getDistanceFromSensor(kTrigFR, kEchoFR);
 
        while (obstacle_R > kCollWallThresh){ // Strafe right till aligned with wall
            strafeRight();
        }
        while (wall_FL < kOriginThresh && wall_FR < kOriginThresh){ // move forward till reach top right corner
            moveForward();
        }
        stopMove();
        
        int currX = 0;
        int currY = 0;
 
        while (currX < kZoneX){
            
        }
        ++state;
     case 3: // Finish execution
        return;
    }
}

void avoidObstacle() {
    int obstacle_FL = getDistanceFromSensor(kTrigFL, kEchoFL);
    int obstacle_FR = getDistanceFromSensor(kTrigFR, kEchoFR);
    if (obstacle_FL < kObstacleThresh) {
        if (obstacle_FR < kObstacleThresh) {
            int random_dir = random(0, 2);
            switch(random_dir) {
              case 0:
                strafeLeft();
                break;
              case 1:
                strafeRight();
                break;
            }
            
            int wall_L;
            int wall_R;
            for (;;) {
                obstacle_FL = getDistanceFromSensor(kTrigFL, kEchoFL);
                obstacle_FR = getDistanceFromSensor(kTrigFR, kEchoFR);
                wall_L = getDistanceFromSensor(kTrigL, kEchoL);
                wall_R = getDistanceFromSensor(kTrigR, kEchoR);
                if (!(obstacle_FL < kObstacleThresh ||
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

#include "motorControllers.h"
#include "ultrasonicSensors.h"
#include "clawController.h"
#include "gyroscope.h"

constexpr int kObstacleThresh = 5;
constexpr int kCollWallThresh = 10;
constexpr int kZoneWallThresh = 200; //TODO
constexpr int kTargetThresh = -1; // TODO

int state;

void setup(){
    setupMotors();
    setupUltrasonicSensors();
    setupClaw();
    setupGyroscope();
    
    state = 0;
}

void loop(){
    switch(state) {
      case 0: // Navigate obstacles
        int obstacle_FL = getDistanceFromSensor(kTrigFL, kEchoFL);
        int obstacle_FR = getDistanceFromSensor(kTrigFR, kEchoFR);
        if (obstacle_FL < kObstacleThresh || obstacle_FR < kObstacleThresh) {
            stopMove();
            avoidObstacle();
            moveForward();
        } else {
            moveForward();
            int wall_L = getDistanceFromSensor(kTrigL, kEchoL);
            int wall_R = getDistanceFromSensor(kTrigR, kEchoR);
            if ((wall_L + wall_R) > kZoneWallThresh) {
                ++state;
            }
        }
      case 1: // Find target
        ++state;
      case 2: // Transport target
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
                wall_L; = getDistanceFromSensor(kTrigL, kEchoL);
                wall_R; = getDistanceFromSensor(kTrigR, kEchoR);
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
        } else {
            return;
        }
    }
}

#include "ultrasonicSensors.h"

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

void setupUltrasonicSensors(){
    for (int i = EchoFrontLeft; i <= TrigBack; i++){
        if (i%2 == 0){ // ECHO PINS MUST BE EVEN PINS
            pinMode(i, INPUT);
        } else { // TRIG PINS MUST BE ODD PINS
            pinMode(i, OUTPUT);
        }
    }
}

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
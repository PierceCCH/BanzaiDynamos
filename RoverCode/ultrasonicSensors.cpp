#include "ultrasonicSensors.h"

void setupUltrasonicSensors(){
    for (int i = kEchoFL; i <= kTrigB; i++){
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
    int distance = pulseIn(echoPin, HIGH) * 0.0343 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    return distance;
}

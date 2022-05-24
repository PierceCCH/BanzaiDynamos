#include "ultrasonicSensors.h"

void setupUltrasonicSensors(){
    for (int i = kEchoFL; i <= kTrigB; i++){
        if (i%2 == 0){ // ECHO PINS MUST BE EVEN PINS
            Serial.print("Echo pin: ");
            Serial.print(i);
            Serial.print('\n');
            pinMode(i, INPUT);
        } else { // TRIG PINS MUST BE ODD PINS
            Serial.print("Trig pin: ");
            Serial.print(i);
            Serial.print('\n');
            pinMode(i, OUTPUT);
        }
    }
    Serial.print("Ultrasonic Sensor Setup Complete");
}

int getDistanceFromSensor(int trigPin, int echoPin){
    // Clear trig pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    // Reads echo and uses return time to calculate the distance
    int distance = duration * 0.0343 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    return distance;
}

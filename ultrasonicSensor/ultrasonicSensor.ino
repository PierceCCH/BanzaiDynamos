// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

constexpr int kEchoFL = 22;
constexpr int kTrigFL = 23;
constexpr int kEchoFM = 24;
constexpr int kTrigFM = 25;
constexpr int kEchoFR = 26;
constexpr int kTrigFR = 27;
constexpr int kEchoL = 28;
constexpr int kTrigL = 29;
constexpr int kEchoR = 30;
constexpr int kTrigR = 31;
constexpr int kEchoB = 32;
constexpr int kTrigB = 33;

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  Serial.begin(9600);
  /*
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
  } */
//  pinMode(kTrigB, OUTPUT);
//  pinMode(kEchoB, INPUT);
//  pinMode(kTrigR, OUTPUT);
//  pinMode(kEchoR, INPUT);
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
  
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(9, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(8, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance B: ");
  Serial.print(distance);
  Serial.println(" cm");

// delay(100);
//    // Clears the trigPin condition
//  digitalWrite(kTrigR, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
//  digitalWrite(kTrigR, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(kTrigR, LOW);
//  // Reads the echoPin, returns the sound wave travel time in microseconds
//  duration = pulseIn(kEchoR, HIGH);
//  // Calculating the distance
//  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
//  // Displays the distance on the Serial Monitor
//  Serial.print("Distance R: ");
//  Serial.print(distance);
//  Serial.println(" cm");
//  delay(100);

}

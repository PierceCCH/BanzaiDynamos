// For motor A
//IN pins in H-Bridge, connect to arduino pins
const int IN1 = 12;
const int IN2 = 11;

// For motor B
const int IN3 = 10;
const int IN4 = 9;

// Analog pins
const int ENA = A0;
const int ENB = A1;

void setup() {
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);

}

void loop() {
  delay(500);
//control speed 
  analogWrite(ENA, 255);
  analogWrite(ENB, 255); 
//control direction 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

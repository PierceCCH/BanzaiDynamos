
// -------------- DEFINE PINS -------------- 
// 
// ---------- MOTORS ----------
// -- RIGHT SIDE
// FRONT RIGHT MOTOR
const int FrontRightF = 13;
const int FrontRightB = 12;
// BACK RIGHT MOTOR
const int BackRightF = 11;
const int BackRightB = 10;
// RIGHT H-Bridge pins
const int ENAright = A0; // Enables motor 
const int ENBright = A1;
// -- LEFT SIDE
// FRONT LEFT MOTOR
const int FrontLeftF = 9;
const int FrontLeftB = 8;
// BACK LEFT MOTOR
const int BackLeftF = 7;
const int BackLeftB = 6;
// LEFT H-Bridge 
const int ENAleft = A2;
const int ENBleft = A3;
// ------------------------------------

void setup() {
  pinMode (FrontRightF, OUTPUT);
  pinMode (FrontRightB, OUTPUT);
  pinMode (BackRightB, OUTPUT);
  pinMode (BackRightF, OUTPUT);
  pinMode (ENAright, OUTPUT);
  pinMode (ENBright, OUTPUT);
  pinMode (FrontLeftF, OUTPUT);
  pinMode (FrontLeftB, OUTPUT);
  pinMode (BackLeftB, OUTPUT);
  pinMode (BackLeftF, OUTPUT);
  pinMode (ENAleft, OUTPUT);
  pinMode (ENBleft, OUTPUT);
}

void loop() {
  delay(500);
  moveForward();
  delay(1500);
  moveBackward();
  delay(500);
}

void enableMove(){
//control speed 
  analogWrite(ENAleft, 255);
  analogWrite(ENBleft, 255); 
  analogWrite(ENAright, 255);
  analogWrite(ENBright, 255); 
}

void moveForward(){
  enableMove();
  digitalWrite(FrontRightF, HIGH);
  digitalWrite(FrontRightB, LOW);
  digitalWrite(BackRightF, HIGH);
  digitalWrite(BackRightB, LOW);
  digitalWrite(FrontLeftF, HIGH);
  digitalWrite(FrontLeftB, LOW);
  digitalWrite(BackLeftF, HIGH);
  digitalWrite(BackLeftB, LOW);
}

void moveBackward(){
  enableMove();
  digitalWrite(FrontRightF, LOW);
  digitalWrite(FrontRightB, HIGH);
  digitalWrite(BackRightF, LOW);
  digitalWrite(BackRightB, HIGH);
  digitalWrite(FrontLeftF, LOW);
  digitalWrite(FrontLeftB, HIGH);
  digitalWrite(BackLeftF, LOW);
  digitalWrite(BackLeftB, HIGH);
}
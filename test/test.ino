#define BLUEpin 2
#define BUTTON 7
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BLUEpin, OUTPUT);
  digitalWrite(BLUEpin, LOW);
  pinMode(BUTTON, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(BUTTON);
  if (buttonState == HIGH){
    digitalWrite(BLUEpin, HIGH);
  } else{
    digitalWrite(BLUEpin, LOW);
  }
}

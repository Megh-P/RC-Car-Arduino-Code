#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

//front or direction motor - Change numbers based on the pin they are put into
int frontMotorPin1=5;
int frontMotorPin2=6;

//back or speed motor
int backMotorPin1=10;
int backMotorPin2=11;

//bool mode = true;

// true = digital
// false = joystick

void setup() {
  
  pinMode(frontMotorPin1,OUTPUT);
  pinMode(frontMotorPin2,OUTPUT);

  pinMode(backMotorPin1, OUTPUT);
  pinMode(backMotorPin2, OUTPUT);

  Serial.begin(9600);
  Dabble.begin(9600, 1, 0);
}

void loop() {
  Dabble.processInput();
  
  joystick();
}
/*
void digital(){
    Dabble.processInput();
    if (GamePad.isUpPressed()) {
    digitalWrite(backMotorPin1, HIGH);
    digitalWrite(backMotorPin2, LOW);
  }
  else if (GamePad.isDownPressed()) {
    digitalWrite(backMotorPin1, LOW);
    digitalWrite(backMotorPin2, HIGH);
  }
  else {
    digitalWrite(backMotorPin1, LOW);
    digitalWrite(backMotorPin2, LOW);
  }
  if (GamePad.isLeftPressed()) {
    digitalWrite(frontMotorPin1, HIGH);
    digitalWrite(frontMotorPin2, LOW);
  }
  else if (GamePad.isRightPressed()) {
    digitalWrite(frontMotorPin1, LOW);
    digitalWrite(frontMotorPin2, HIGH);
  }
  else {
    digitalWrite(frontMotorPin1, LOW);
    digitalWrite(frontMotorPin2, LOW);
  }
}
*/
void joystick() {
  Dabble.processInput();
  double joyX = GamePad.getXaxisData();  // Read the X-axis value of the joystick
  double joyY = GamePad.getYaxisData();  // Read the Y-axis value of the joystick
  
  if (joyX > 1){
    digitalWrite(frontMotorPin1, LOW);
    digitalWrite(frontMotorPin2, HIGH);
    right(joyX);
  }
  else if (joyX < -1) {
    digitalWrite(frontMotorPin1, HIGH);
    digitalWrite(frontMotorPin2, LOW);
    left(joyX);
  }
  else {
    digitalWrite(frontMotorPin1, LOW);
    digitalWrite(frontMotorPin2, LOW);
  }
  
  if (joyY > 1){
    digitalWrite(backMotorPin1, HIGH);
    digitalWrite(backMotorPin2, LOW);
    forward(joyY);
  }
  else if (joyY < -1) {
    digitalWrite(backMotorPin1, LOW);
    digitalWrite(backMotorPin2, HIGH);
    back(joyY);
  }
  else {
    digitalWrite(backMotorPin1, LOW);
    digitalWrite(backMotorPin2, LOW);
  }
}

void forward(double joyY) {
  analogWrite(backMotorPin1, joyY);
}
void back(double joyY) {
  analogWrite(backMotorPin2, joyY);
}
void right(double joyX) {
  analogWrite(frontMotorPin2, joyX);
}
void left(double joyX) {
  analogWrite(frontMotorPin1, joyX);
}
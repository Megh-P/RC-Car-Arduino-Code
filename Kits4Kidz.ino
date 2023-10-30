#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

//front or direction motor - Change numbers based on the pin they are put into
int enableFrontMotor=9; 
int frontMotorPin1=7;
int frontMotorPin2=8;

//back or speed motor 
int enableBackMotor=6;
int backMotorPin1=9;
int backMotorPin2=10;

void setup() {
  
// front motor
  pinMode(enableFrontMotor, OUTPUT);
  pinMode(frontMotorPin1, OUTPUT);
  pinMode(frontMotorPin2, OUTPUT);
  
  
// back motor
  pinMode(enableBackMotor, OUTPUT);
  pinMode(backMotorPin1, OUTPUT);
  pinMode(backMotorPin2, OUTPUT);

  Serial.begin(25000);
  Dabble.begin(9600,0,1);
}

void loop() {
  Dabble.processInput();
  
  int frontMotor = 0;
  int backMotor = 0;
  if (GamePad.isUpPressed()) {
    Serial.println("it works");
    frontMotor = 255;
    backMotor = 255;
  }

  float joyX = GamePad.getXaxisData();  // Read the X-axis value of the joystick
  float joyY = GamePad.getYaxisData();  // Read the Y-axis value of the joystick

  // Map joystick values to motor speeds
  // int frontMotor = map(joyX, -7, 7, -255, 255);
  // int backMotor = map(joyY, -7, 7, -255, 255);  // Map joysticks

  
  rotateMotors(frontMotor, backMotor);
}

void rotateMotors(int directionMotor, int speedMotor) {
  if (abs(directionMotor) > 35) {  
    if (directionMotor < 0) { // direction motor will turn backwards
      digitalWrite(frontMotorPin1, LOW);
      digitalWrite(frontMotorPin2, HIGH);
    }
    else if (directionMotor > 0) {
      digitalWrite(frontMotorPin1, HIGH);
      digitalWrite(frontMotorPin2, LOW);
    } 
    else {
      digitalWrite(frontMotorPin1, LOW);
      digitalWrite(frontMotorPin2, LOW);
    }
  }

  if (abs(speedMotor) > 35) {
    if (speedMotor < 0){
      digitalWrite(backMotorPin1, LOW);
      digitalWrite(backMotorPin2, HIGH);
    }
    else if (speedMotor > 0) {
      digitalWrite(backMotorPin1, HIGH);
      digitalWrite(backMotorPin2, LOW);
    }
    else {
      digitalWrite(backMotorPin1, LOW);
      digitalWrite(backMotorPin2, LOW);
    }
  }
  
  analogWrite(enableFrontMotor, abs(directionMotor));
  analogWrite(enableBackMotor, abs(speedMotor)); 
}
/*
Input1	Input2	Spinning Direction
Low(0)	Low(0)	Motor OFF
High(1)	Low(0)	Forward
Low(0)	High(1)	Backward
High(1)	High(1)	Motor OFF
*/

/*
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

// front or direction motor - Change numbers based on the pin they are put into
int enableFrontMotor = 5;
int frontMotorPin1 = 7;
int frontMotorPin2 = 8;

// back or speed motor
int enableBackMotor = 6;
int backMotorPin1 = 9;
int backMotorPin2 = 10;

// Calibration table for the front motor
const int numReferencePositions = 3;
const int referencePositions[numReferencePositions] = {0, 90, 180};
const float measuredTimeIntervals[numReferencePositions] = {0.0, 1.20, 2.50};

void setup() {

  // front motor
  pinMode(enableFrontMotor, OUTPUT);
  pinMode(frontMotorPin1, OUTPUT);
  pinMode(frontMotorPin2, OUTPUT);

  // back motor
  pinMode(enableBackMotor, OUTPUT);
  pinMode(backMotorPin1, OUTPUT);
  pinMode(backMotorPin2, OUTPUT);

  Serial.begin(25000);
  Dabble.begin(9600);
}

void loop() {
  Dabble.processInput();

  float joyX = GamePad.getXaxisData();  // Read the X-axis value of the joystick
  float joyY = GamePad.getYaxisData();  // Read the Y-axis value of the joystick

  // Map joystick values to motor speeds
  int frontMotor = map(joyX, -7, 7, -255, 255);
  int backMotor = map(joyY, -7, 7, -255, 255);  // Map joysticks

  int estimatedPosition = estimateFrontMotorPosition(frontMotor);
  Serial.print("Estimated Front Motor Position: ");
  Serial.println(estimatedPosition);

  rotateMotors(frontMotor, backMotor);
}

void rotateMotors(int directionMotor, int speedMotor) {
  // Same as in the original code
  // ...
}

int estimateFrontMotorPosition(int directionMotor) {
  // Find the corresponding measured time interval in the calibration table
  float measuredTime = map(abs(directionMotor), 0, 255, 0, measuredTimeIntervals[numReferencePositions - 1]);

  // Interpolation to estimate the position based on the calibration table
  int estimatedPosition = 0;
  for (int i = 0; i < numReferencePositions - 1; i++) {
    if (measuredTime >= measuredTimeIntervals[i] && measuredTime <= measuredTimeIntervals[i + 1]) {
      float t = (measuredTime - measuredTimeIntervals[i]) / (measuredTimeIntervals[i + 1] - measuredTimeIntervals[i]);
      estimatedPosition = map(t, 0, 1, referencePositions[i], referencePositions[i + 1]);
      break;
    }
  }
  return estimatedPosition;
}
*/
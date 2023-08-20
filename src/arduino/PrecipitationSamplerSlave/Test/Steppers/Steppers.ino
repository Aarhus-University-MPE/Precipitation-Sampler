#include <AccelStepper.h>

// Define pin connections & motor's steps per revolution
const int dirPin        = 2;
const int stepPinHeight = 6;
const int stepPinPump   = 3;
const int stepPinWheel  = 5;

uint8_t process = 0;
unsigned long lastMillis;

AccelStepper stepperHeight(1, stepPinHeight, dirPin);  // (X, Y , Z)  X =
AccelStepper stepperPump(1, stepPinPump, dirPin);      // (X, Y , Z)  X =
AccelStepper stepperWheel(1, stepPinWheel, dirPin);    // (X, Y , Z)  X =

void setup() {
  // Declare pins as Outputs
  pinMode(stepPinHeight, OUTPUT);
  pinMode(stepPinPump, OUTPUT);
  pinMode(stepPinWheel, OUTPUT);

  digitalWrite(8, LOW);

  stepperHeight.setMaxSpeed(5000);
  stepperHeight.setAcceleration(500);
  stepperHeight.setPinsInverted(false, false, true);  // Invertere signalet
  stepperPump.setMaxSpeed(5000);
  stepperPump.setAcceleration(500);
  stepperPump.setPinsInverted(false, false, true);  // Invertere signalet
  stepperWheel.setMaxSpeed(5000);
  stepperWheel.setAcceleration(500);
  stepperWheel.setPinsInverted(false, false, true);  // Invertere signalet

  stepperHeight.setSpeed(600);
  stepperPump.setSpeed(400);
  stepperWheel.setSpeed(100);
}
void loop() {
  stepperHeight.runSpeed();
  stepperPump.runSpeed();
  stepperWheel.runSpeed();
}
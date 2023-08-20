/*
    MAKE SURE THE NEEDLE IS CLEAR OF THE WHEEL BEFORE RUNNING THIS TEST
*/

#include <AccelStepper.h>

#define PI_SWITCH_UPPER 13  // Sample wheel encoding switch (Sample hole)
#define PI_SWITCH_LOWER 11  // Sample wheel encoding switch (Flush hole)

#define PO_WHEEL_STP    3    // Sample Wheel stepper-step signal
#define WHEEL_MAX_SPEED 500  // Wheel MAX speed (Steps/s)
#define WHEEL_ACC       100  // Wheel Acceleration (Steps/s^2)

#define ANALOG_HIGH     512

bool switchA = false;  // Encoder Switch (Upper) - Sample Position
bool switchB = false;  // Encoder Switch (Lower) - Purge Position

uint8_t stepperProcess = 0;  // Process variable

// Setup Wheel stepper
AccelStepper stepperWheel(1, PO_WHEEL_STP, 0);

void setup() {
  pinMode(PO_WHEEL_STP, OUTPUT);
  pinMode(PI_SWITCH_UPPER, INPUT);
  pinMode(PI_SWITCH_LOWER, INPUT);

  stepperWheel.setPinsInverted(false, false, true);  // Invertere signalet
  stepperWheel.setMaxSpeed(WHEEL_MAX_SPEED);         // Max. hastighed    (steps/sek.)
  stepperWheel.setAcceleration(WHEEL_ACC);           // Max. acceleration (steps/sek.^2)
  stepperWheel.setCurrentPosition(0);
}

void loop() {
  switch (stepperProcess) {
    case 0:  // Homing Procedure
      if (WheelMoveHome()) {
        stepperProcess++;
        delay(1000);
      }
      break;

    case 1:  // Move to first purge
      if (WheelMovePurge()) {
        stepperProcess++;
        delay(1000);
      }
      break;

    case 2:  // Move to first Sample
      if (WheelMoveSampling()) {
        stepperProcess++;
        delay(1000);
      }
      break;

    case 3:  // Repeat purge -> sample -> purge
      stepperProcess = 1;
      break;

    default:
      stepperProcess = 0;
      break;
  }
}

// Read Encoder Switch positions
void ReadWheelSwitches() {
  switchA = analogRead(PI_SWITCH_UPPER) >= ANALOG_HIGH;
  switchB = analogRead(PI_SWITCH_LOWER) >= ANALOG_HIGH;
}

// Move to home position (Purge)
bool WheelMoveHome() {
  ReadWheelSwitches();

  // Zero motor, if at home position
  if (switchA && switchB) {
    stepperWheel.setCurrentPosition(0);
    return true;
  }

  // Continue running motor
  stepperWheel.runSpeed();
  return false;
}

// Rotate wheel to sampling position
bool WheelMoveSampling() {
  ReadWheelSwitches();

  // Check if currently at sample position
  if (switchA && !switchB) return true;

  // Continue running motor
  stepperWheel.runSpeed();
  return false;
}

// Rotate wheel to purge position
bool WheelMovePurge() {
  ReadWheelSwitches();

  // Check if currently at purge position
  if (!switchA && switchB) return true;

  // Continue running motor
  stepperWheel.runSpeed();
  return false;
}

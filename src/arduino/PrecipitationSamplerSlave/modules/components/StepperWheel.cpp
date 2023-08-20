#pragma once

#include "../setup/modules.h"

AccelStepper stepperWheel(PO_STEPPER_EN, PO_WHEEL_STP, 0);

bool switchA = false;  // Encoder Switch (Upper) - Sample Position
bool switchB = false;  // Encoder Switch (Lower) - Purge Position

// Initialize Wheel Stepper Motor
void InitStepperWheel() {
  stepperWheel.setPinsInverted(false, false, true);  // Invertere signalet
  stepperWheel.setMaxSpeed(WHEEL_MAX_SPEED);         // Max. hastighed    (steps/sek.)
  stepperWheel.setAcceleration(WHEEL_ACC);           // Max. acceleration (steps/sek.^2)
  stepperWheel.setCurrentPosition(0);
  DisableStepperWheel();
}

// Enable Wheel Stepper Motor
void EnableStepperWheel() {
  stepperWheel.enableOutputs();
}

// Disable Wheel Stepper Motor
void DisableStepperWheel() {
  stepperWheel.disableOutputs();
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

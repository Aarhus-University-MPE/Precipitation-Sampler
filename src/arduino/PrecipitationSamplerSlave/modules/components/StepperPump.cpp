#pragma once

#include "../setup/modules.h"

// Setup Pump Stepper
AccelStepper stepperPump(PO_STEPPER_EN, PO_PUMP_STP);

// Initialize Stepper Motor for Pump Control
void InitStepperPump() {
  stepperPump.setPinsInverted(false, false, true);  // Inverts the "direction" pin
  stepperPump.setMaxSpeed(PUMP_MAX_SPEED);          // Max. hastighed    (steps/sek.)
  stepperPump.setAcceleration(PUMP_ACC);            // Max. acceleration (steps/sek.^2)
  stepperPump.setCurrentPosition(0);                // Set the start position to 0
  DisableStepperPump();                             // Stepper is OFF on startup
}

// Enable Pump Stepper Motor
void EnableStepperPump() {
  stepperPump.enableOutputs();
}

// Disable Pump Stepper Motor
void DisableStepperPump() {
  stepperPump.disableOutputs();
}

// Run Pump Stepper motor for Sample Duration
bool PumpMoveSampling() {
  if (stepperPump.currentPosition() != PUMP_SAMPLING_END) {
    stepperPump.moveTo(PUMP_SAMPLING_END);
    stepperPump.run();
    return false;
  } else {
    stepperPump.setCurrentPosition(0);
    return true;
  }
}

// Run Pump Stepper motor for Purge Duration
bool PumpMovePurge() {
  if (stepperPump.currentPosition() != PUMP_PURGE) {
    stepperPump.moveTo(PUMP_PURGE);
    stepperPump.run();
    return false;
  } else {
    stepperPump.setCurrentPosition(0);
    return true;
  }
}

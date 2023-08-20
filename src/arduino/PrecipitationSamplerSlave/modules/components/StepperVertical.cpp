/*
    Real Time Clock handles timing using a Pmod RTCC (https://digilent.com/reference/pmod/pmodrtcc/start?redirect=1)

    Primary library: https://digilent.com/reference/_media/reference/pmod/pmodrtcc/rtcci2c.zip
    - Modified to latest Wire.h convention (Wire.receive() -> Wire.read() & Wire.send(xx) -> Wire.write(xx))
    Secondary library: https://github.com/PaulStoffregen/Time

    By
    Mads Rosenhoej Jeppesen - Aarhus 2021
    mrj@mpe.au.dk
*/

#pragma once

#include "../setup/modules.h"

AccelStepper stepperVertical(PO_STEPPER_EN, PO_VERTICAL_STP, PO_VERTICAL_DIR);

// Motor Initialization
void InitStepperVertical() {
  stepperVertical.setPinsInverted(false, false, true);  // Inverted Signal Pins
  stepperVertical.setMaxSpeed(VERTICAL_MAX_SPEED);      // Max. velocity    (steps/sec.)
  stepperVertical.setAcceleration(VERTICAL_ACC);        // Max. acceleration (steps/sec.^2)
  stepperVertical.setCurrentPosition(0);
  DisableStepperVertical();
}

// Enable Vertical Stepper Motor
void EnableStepperVertical() {
  stepperVertical.enableOutputs();
}

// Disable Vertical Stepper Motor
void DisableStepperVertical() {
  stepperVertical.disableOutputs();
}

// Homing Stepper Switch
bool ReadVerticalSwitch() {
  return analogRead(PI_SWITCH_VERTICAL) >= ANALOG_HIGH;
}

// Move clear of the capsule feeder // TODO: Can cause error if started at unknown position (lower position, will move into itself)
bool VerticalMoveClear() {
  if (stepperVertical.currentPosition() == VERTICAL_CLEARING) return true;

  // Move towards clearing
  stepperVertical.moveTo(VERTICAL_CLEARING);
  stepperVertical.run();

  return false;
}

// Move towards Home position (Top)
bool VerticalMoveHome() {
  if (ReadVerticalSwitch()) {
    stepperVertical.setCurrentPosition(0);
    return true;
  }

  stepperVertical.setSpeed(-VERTICAL_MAX_SPEED);
  stepperVertical.runSpeed();
  return false;
}

/*
  Lid motor controller, utilizing a Rotiny motor

  Mads Rosenhøj Jepepsen
  Aarhus University
  2022
*/

#pragma once
#include "../setup/modules.h"

unsigned long motorStartMillis = 0;
uint8_t homingState            = 0;

// Homing Stepper Switch
bool ReadHomeSwitch() {
  return analogRead(PI_SWITCH_LID) >= ANALOG_HIGH;
}

// Move Lid motor
void LidMove(bool open) {
  if (open && digitalRead(PO_LID_OPEN)) return;
  if (!open && digitalRead(PO_LID_CLOSE)) return;

  if (open) {
    digitalWrite(PO_LID_CLOSE, false);
    digitalWrite(PO_LID_OPEN, true);
  } else {
    digitalWrite(PO_LID_OPEN, false);
    digitalWrite(PO_LID_CLOSE, true);
  }

  // Set Start timestamp
  motorStartMillis = millis();
}

// Stop Lid Motor
void LidStop() {
  digitalWrite(PO_LID_CLOSE, false);
  digitalWrite(PO_LID_OPEN, false);
}

// Rotate towards home position
bool LidMoveHome() {
  if (ReadHomeSwitch()) {
    LidStop();
    return true;
  }

  LidMove(false);
  return false;
}

// Rotate towards open position
bool LidMoveOpen() {
  if (millis() - motorStartMillis > LID_OPEN_DURATION) {
    LidStop();
    return true;
  }

  LidMove(true);
  return false;
}

// Rotate towards open position for a short duration
bool LidMoveOpenSmall() {
  if (millis() - motorStartMillis > LID_SMALLOPEN_DURATION) {
    LidStop();
    return true;
  }

  LidMove(true);
  return false;
}

// Homing procedure
bool LidHome() {
  switch (homingState) {
    case 0:  // Checkif already at home position
      if (ReadHomeSwitch()) {
        homingState++;
      } else {  // Skip moving clear if not at home position
        homingState += 2;
      }
      break;

    case 1:  // Open Slightly
      if (LidMoveOpenSmall()) homingState++;
      break;

    case 2:  // Move towards home position
      if (LidMoveHome()) {
        homingState = 0;
        return true;
      }
      break;

    default:
      break;
  }

  return false;
}

#pragma once

#include "../setup/modules.h"

uint8_t homingState        = 0;
uint8_t stepperSampleState = 0;

// Initialize Stepper Motors
void StepperInitialize() {
  homingState        = 0;
  stepperSampleState = 0;

  InitStepperWheel();
  InitStepperVertical();
  InitStepperPump();
}

// Enable Stepper Motors
void StepperEnable() {
  EnableStepperWheel();
  EnableStepperVertical();
  EnableStepperPump();
}

// Disable Stepper Motors
void StepperDisable() {
  DisableStepperWheel();
  DisableStepperVertical();
  DisableStepperPump();
}

// Motor Homing Procedure
bool StepperHoming() {
  switch (homingState) {
    case 0:  // Check if at top Position
      if (ReadVerticalSwitch()) {
        homingState++;
      } else {  // Skip moving clear if not at top position
        homingState += 2;
      }
      break;

    case 1:  // If at top Position, Move Up (Clear of Needle)
      if (VerticalMoveClear()) homingState++;
      break;

    case 2:  // Rotate to home position (Purge position)
      if (WheelMoveHome()) homingState++;
      break;

    case 3:  // Move to top Position (Home)
      if (VerticalMoveHome()) homingState++;
      break;

    case 4:  // Move Up (Clear of Needle)
      if (VerticalMoveClear()) homingState++;
      break;

    case 5:  // Rotate to purge position
      if (WheelMovePurge()) homingState++;
      break;

    case 6:  // Home vertical (Final Step)
      if (VerticalMoveHome()) {
        homingState = 0;
        return true;
      }
      break;

    default:
      homingState = 0;
      break;
  }

  return false;
}

// Full Stepper Sample Cycle
bool StepperSampleCycle() {
  switch (stepperSampleState) {
    case 0:  // Purge
      if (PumpMovePurge()) stepperSampleState++;
      break;

    case 1:  // Move Up (Clear of Needle)
      if (VerticalMoveClear()) stepperSampleState++;
      break;

    case 2:  // Rotate to Sample
      if (WheelMoveSampling()) stepperSampleState++;
      break;

    case 3:  // Move Down
      if (VerticalMoveHome()) stepperSampleState++;
      break;

    case 4:  // Fill Sample
      if (PumpMoveSampling()) stepperSampleState++;
      break;

    case 5:  // Move Up (Clear of Needle)
      if (VerticalMoveClear()) stepperSampleState++;
      break;

    case 6:  // Rotate to Purge
      if (WheelMovePurge()) stepperSampleState++;
      break;

    case 7:  // Move Down
      if (VerticalMoveHome()) stepperSampleState++;
      break;

    case 8:  // Purge
      uint8_t purgeCounts = 0;
      if (PumpMovePurge()) purgeCount++;

      if (purgeCounts >= FINAL_PURGE_COUNT) {
        stepperSampleState = 0;
        return true;
      }
      break;

    default:
      stepperSampleState = 0;
      break;
  }
  return false;
}
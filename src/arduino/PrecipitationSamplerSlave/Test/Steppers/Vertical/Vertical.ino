/*
    MAKE SURE THE WHEEL IS TURNED TO "ZERO" POSITION BEFOR RUNNING THIS TEST!!!

    Runs homing process at startup (with 1 second break after every position is reached)
*/

#include <AccelStepper.h>

#define PO_STEPPER_EN      4   // Stepper enable signal to all steppers
#define PO_VERTICAL_STP    5   // Height stepper-step signal
#define PO_VERTICAL_DIR    7   // Height stepper direction signal
#define PI_SWITCH_VERTICAL 12  // Height limmitswitch

#define ANALOG_HIGH        512

// VERTICAL STEPPER
#define VERTICAL_MAX_SPEED 300
#define VERTICAL_ACC       100
#define VERTICAL_CLEARING  200  // How many steps to be clear of needles  TODO: Verify

// Setup Pump stepper
AccelStepper stepperVertical(PO_STEPPER_EN, PO_VERTICAL_STP, PO_VERTICAL_DIR);

// Related compoents
bool heightSwitch;
uint8_t homingState = 0;  // Process handling

void setup() {
  pinMode(PO_VERTICAL_DIR, OUTPUT);
  pinMode(PO_VERTICAL_STP, OUTPUT);
  pinMode(PI_SWITCH_VERTICAL, INPUT);

  stepperVertical.setPinsInverted(false, false, true);  // Inverted Signal Pins
  stepperVertical.setMaxSpeed(VERTICAL_MAX_SPEED);      // Max. velocity    (steps/sec.)
  stepperVertical.setAcceleration(VERTICAL_ACC);        // Max. acceleration (steps/sec.^2)
  stepperVertical.setCurrentPosition(0);
}

void loop() {
  StepperHoming();

  delay(1000);
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

    case 1:  // If at top Position, Move Down (Clear of Needle)
      if (VerticalMoveClear()) homingState++;
      break;

    case 2:  // Wait 1 second
      delay(1000);
      homingState++;
      break;

    case 3:  // Move to top Position (Home)
      if (VerticalMoveHome()) homingState++;
      break;

    case 4:  // Wait 1 second
      delay(1000);
      homingState++;
      break;

    case 5:  // Move Down (Clear of Needle)
      if (VerticalMoveClear()) {
        homingState = 0;
        homingState++;
        return true;
      }
      break;

    case 6:  // Do nothing
      break;

    default:
      homingState = 0;
      break;
  }

  return false;
}

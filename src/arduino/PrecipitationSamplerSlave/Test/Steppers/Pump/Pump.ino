/*
    MAKE SURE THE WHEEL IS TURNED TO "ZERO" POSITION BEFOR RUNNING THIS TEST!!!

    On startup runs pump for sample duration, waits 2 seconds and then purge duration
*/

#include <AccelStepper.h>

#define PO_STEPPER_EN     4      // Stepper enable signal to all steppers
#define PO_PUMP_STP       6      // Pump stepper-step signal
#define PUMP_MAX_SPEED    2000   // Pump max speed (Steps/s)
#define PUMP_ACC          200    // Pump Acceleration (Steps/s^2)
#define PUMP_SAMPLING_END 3200   // How many steps to do make a sample (3200 approximately 2mL)    TODO: Verify
#define PUMP_PURGE        13000  // How many steps to do a full purge (13000 approximately 8,125 mL)     TODO: Verify

uint32_t PUMP_PURGE = PUMP_SAMPLING_END * 7;  // How many steps to do a fulle purge.

// Setup Pump stepper
AccelStepper Pump(PO_STEPPER_EN, PO_PUMP_STP, 0);

// Related compoents
uint8_t process = 0;  // Process handling

void setup() {
  Serial.begin(9600);
  pinMode(PO_PUMP_STP, OUTPUT);

  // Opsætning af Steppermotor
  Pump.setPinsInverted(false, false, true);  // Inverts the "direction" pin
  Pump.setMaxSpeed(PUMP_MAX_SPEED);          // Max. hastighed    (steps/sek.)
  Pump.setAcceleration(PUMP_ACC);            // Max. acceleration (steps/sek.^2)
  Pump.setCurrentPosition(0);                // Set the start position to 0
  Pump.setSpeed(1000);
  Serial.println("Signal Opened");
}

void loop() {
  switch (process) {
    case 0:  // Run pump for sampling
      if (PumpMoveSampling()) process++;
      break;

    case 1:  // Wait 2 seconds
      delay(2000);
      process++;

    case 2:  // Run pump for purge
      if (PumpMovePurge()) process++;
      break;

    case 3:  // Do Nothing
      break;

    default:  // Set case to 0 if something is wrong
      process = 0;
      break;
  }
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

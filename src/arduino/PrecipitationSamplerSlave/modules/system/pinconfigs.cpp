#pragma once

#include "../setup/modules.h"

// Sets pinmode of all pins and writes initial values for outputs
void InitializePins() {
  // Pinmode for Arduino/Arduino coms
  pinMode(PO_ARDUINO_COM, INPUT);

  // Pinmode for StepperMotors
  pinMode(PO_STEPPER_EN, OUTPUT);
  pinMode(PO_WHEEL_STP, OUTPUT);
  pinMode(PO_VERTICAL_STP, OUTPUT);
  pinMode(PO_PUMP_STP, OUTPUT);
  pinMode(PO_VERTICAL_DIR, OUTPUT);

  // Pinmode for Heating Elements
  pinMode(PO_HEAT_FUNNEL, OUTPUT);
  pinMode(PO_HEAT_PUMP, OUTPUT);

  // Pinmode for Mechanical switches
  pinMode(PI_SWITCH_UPPER, INPUT);
  pinMode(PI_SWITCH_LOWER, INPUT);
  pinMode(PI_SWITCH_VERTICAL, INPUT);

  // Pinmode for Temperature sensors
  pinMode(PA_TEMP_FUNNEL, INPUT);
  pinMode(PA_TEMP_PUMP, INPUT);

  // Pinmode for Load cells
  pinMode(PI_LOADCELL_DT, INPUT);
  pinMode(PI_LOADCELL_SCK, INPUT);
}

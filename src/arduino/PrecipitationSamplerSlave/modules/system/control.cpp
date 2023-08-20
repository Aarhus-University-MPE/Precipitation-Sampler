#pragma once

#include "../setup/modules.h"

// Enables Primary Systems
void SystemEnablePrimary() {
  InitializePins();
}

// Enables Secondary Systems
void SystemEnableSecondary() {
  StepperEnable();
}

// Disable Secondary Systems
void SystemDisableSecondary() {
  StepperDisable();
  DisableHeating();
}

// Function Called when Master Wakes Slave (indicating a Sample Start Command)
void WakeFunction() {
  sleep_disable();                                         // Disable sleep mode
  detachInterrupt(digitalPinToInterrupt(PO_ARDUINO_COM));  // detach wakeup function

  // Wake systems and flag sample start
  SystemEnableSecondary();
  StartSample();
}

// Primary sleep function
void Sleep() {
  // Power OFF secondary systems (motors, heating)
  SystemDisableSecondary();

  // Attach wakeup function
  attachInterrupt(digitalPinToInterrupt(PO_ARDUINO_COM), WakeFunction, HIGH);

  // Sleep
  sleep_enable();                       // Enable sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Full power down
  delay(500);                           // Wait 500 ms before going fully to sleep
  sleep_cpu();                          // Power down CPU
}

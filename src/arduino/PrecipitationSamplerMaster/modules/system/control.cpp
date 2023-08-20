#pragma once

#include "../setup/modules.h"

// Enables Primary Systems
void SystemEnablePrimary() {
  InitializePins();

  InitializeSDReader();
  InitializeRTC();
  InitializeLoadcell();
}

// Enables Secondary Systems
void SystemEnableSecondary() {
}

// Disable Secondary Systems
void SystemDisableSecondary() {
  LidStop();
}

// Function Called when Master Wakes Slave (indicating a Sample Start Command)
void WakeFunction() {
  sleep_disable();                                       // Disable sleep mode
  detachInterrupt(digitalPinToInterrupt(PT_RTC_ALARM));  // detach wakeup function

  DisableAlarm();

  // Wake systems and flag sample start
  SystemEnableSecondary();
}

// Primary sleep function
void Sleep(uint32_t duration) {
  // Power OFF secondary systems (motors, heating)
  SystemDisableSecondary();

  SetAlarm(duration);

  // Attach wakeup function
  attachInterrupt(digitalPinToInterrupt(PT_RTC_ALARM), WakeFunction, FALLING);

  // Sleep
  sleep_enable();                       // Enable sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Full power down
  delay(500);                           // Wait 500 ms before going fully to sleep
  sleep_cpu();                          // Power down CPU
}

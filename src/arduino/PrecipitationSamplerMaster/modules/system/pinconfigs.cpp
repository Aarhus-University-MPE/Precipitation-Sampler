#pragma once

#include "../setup/modules.h"

// Sets pinmode of all pins and writes initial values for outputs
void InitializePins() {
  // Pinmode for Arduino/Arduino coms
  pinMode(PI_ARDUINO_COM, INPUT);

  // Pinmode for RTC module
  pinMode(PT_RTC_ALARM, INPUT_PULLUP);
  pinMode(PO_RTC_DATA, OUTPUT);
  pinMode(PO_RTC_CLK, OUTPUT);

  // Pinmode for DC-motor
  pinMode(PO_LID_OPEN, OUTPUT);
  pinMode(PO_LID_CLOSE, OUTPUT);

  // Pinmode for distance sensor
  pinMode(PA_DIST_SENSE, INPUT);

  // Pinmode for SD-card
  pinMode(PI_SD_MISO, INPUT);
  pinMode(PO_SD_MOSI, OUTPUT);
  pinMode(PO_SD_CS, OUTPUT);
  pinMode(PO_SD_SCK, OUTPUT);

  // Pinmode for Mechanical switches
  pinMode(PI_SWITCH_LID, INPUT);
}

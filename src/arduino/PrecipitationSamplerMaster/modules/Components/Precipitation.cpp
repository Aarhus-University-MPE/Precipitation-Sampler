/*
  Precipitation Detection Functions
*/

#pragma once

#include "../setup/modules.h"

// Returns true if number of hits surpass minimum
bool DetectPrecipitation() {
  unsigned long millisSampleStart = millis();
  unsigned long lastMillisDetect  = millis() - DETECT_PERIOD;

  uint8_t hitCount = 0;  // Number of hits detected within sample duration

  // Begin sampling
  while (millis() - millisSampleStart > DETECT_DURATION || hitCount > DETECT_COUNT) {
    if (millis() - lastMillisDetect > DETECT_PERIOD) {
      lastMillisDetect = millis();
      if (analogRead(PA_DIST_SENSE) < DETECT_VALUE_MIN) hitCount++;  // Increment hitcount
    }
  }

  return hitCount > DETECT_COUNT;
}
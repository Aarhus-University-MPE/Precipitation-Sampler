/*
  Precipitation Loadcell functionalities
  Utilizing HX711 Analog to Digital converter connected to a set of load cells
*/

#pragma once

#include "../setup/modules.h"

HX711 scale;
float lastScaleValue = 0;

// Initialize Loadcells
void InitializeLoadcell() {
  scale.begin(PI_LOADCELL_DT, PI_LOADCELL_SCK);

  scale.set_scale();
  scale.tare();
}

// Tare (Re-zero) the load cell
void TareLoadcell() {
  scale.tare();
}

// Returns the load cell weight
float LoadcellWeight() {
  return scale.get_units(10);
}

// Returns true if Loadcell value has increased in value above minimum required
bool LoadcellIncrease() {
  float newScaleValue = LoadcellWeight();

  bool loadcellIncreased = newScaleValue - lastScaleValue > LOADCELL_INCREASE_MIN;

  // Update last scale
  lastScaleValue = newScaleValue;

  return loadcellIncreased;
}

// Returns true if Load cell value is above
bool LoadcellFull() {
  return lastScaleValue > LOADCELL_FULL_MIN;
}
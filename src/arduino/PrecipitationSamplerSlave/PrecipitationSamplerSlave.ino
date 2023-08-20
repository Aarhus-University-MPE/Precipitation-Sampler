/*
  Primary Control System for Precipitation Sampler Slave Module
  Handles primary sampling process.

  By:
    Mads Rosenhøj Jeppesen
    Aarhus University
    2023

*/
#include "./modules/setup/modules.h"

// Initialization Process
void setup() {
  SystemEnablePrimary();  // Primary systems (Pins)

  StepperInitialize();
  SystemEnableSecondary();  // Enable Secondary Systems (Steppers, Heating)

  // Allow System to heat up before running motors TODO: System should always be sufficiently hot on installation?
  // while (!HeatingSufficient()) {
  //   HeatignProcess();
  // }

  while (!StepperHoming()) {
    ;  // Wait for homine to finish
  }

  ResetSample();
}

void loop() {
  while (!SampleActive()) {
    Sleep();
  }

  HeatingProcess();
  SamplingProcess();
}
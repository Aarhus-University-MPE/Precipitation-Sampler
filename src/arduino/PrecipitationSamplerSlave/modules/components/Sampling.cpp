/*
  Primary Sampling Functions for Precipitation Sampler Slave Module

  By:
    Mads Rosenhøj Jeppesen
    Aarhus University
    2023
*/
#pragma once

#include "../setup/modules.h"

uint8_t sampleState  = 0;
uint8_t sampleNumber = 0;
bool sampleActive    = false;

// Returns true if sample is currently active
bool SampleActive() {
  return sampleActive;
}

// Initialize Sampling
void StartSample() {
  pinMode(PO_ARDUINO_COM, OUTPUT);
  digitalWrite(PO_ARDUINO_COM, true);  // Communicate Sampling has begun
  sampleState = 0;
}

// Resets sampling process (Run on system boot-up)
void ResetSample() {
  sampleActive = false;
  sampleState  = 0;
  sampleNumber = 0;

  digitalWrite(PO_ARDUINO_COM, false);
  pinMode(PO_ARDUINO_COM, INPUT);
}

// Complete sample
void EndSample() {
  sampleActive = false;
  sampleState  = 0;

  digitalWrite(PO_ARDUINO_COM, false);
  pinMode(PO_ARDUINO_COM, INPUT);
}

// Primary Sampling Process
void SamplingProcess() {
  switch (sampleState) {
    case 0:  // Check heating status
      if (HeatingSufficient()) sampleState++;
      break;

    case 1:  // Sampling loop
      if (StepperSampleCycle()) sampleState++;
      break;

    case 2:  // Sample Complete
      EndSample();
      break;

    default:
      sampleState = 0;
      break;
  }
}
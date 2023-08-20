#pragma once

#include "./modules.h"

// SYSTEM
void InitializePins();
void SystemEnablePrimary();
void SystemEnableSecondary();
void Sleep();

// Sampling
void StartSample();
void ResetSample();
bool SampleActive();
void SamplingProcess();
void DoSampling();

// Heating
void InitHeating();
void HeatingProcess();
bool HeatingSufficient();
void HeatingWait();
void DisableHeating();

// Stepper Control
void StepperInitialize();
void StepperDisable();
void StepperEnable();
bool StepperHoming();
bool StepperSampleCycle();

// Wheel
void InitStepperWheel();
void EnableStepperWheel();
void DisableStepperWheel();
bool WheelMoveHome();
bool WheelMoveSampling();
bool WheelMovePurge();

// Vertical
void InitStepperVertical();
void EnableStepperVertical();
void DisableStepperVertical();
bool VerticalMoveHome();
bool VerticalMoveClear();
bool ReadVerticalSwitch();

// Pump
void InitStepperPump();
void EnableStepperPump();
void DisableStepperPump();
bool PumpMoveSampling();
bool PumpMovePurge();

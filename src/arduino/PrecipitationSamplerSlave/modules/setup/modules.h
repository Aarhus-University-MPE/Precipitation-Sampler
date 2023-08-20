#pragma once

// Internal Libraries
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// External Libraries
#include <AccelStepper.h>

// Config
#include "../../Config/constants.h"
#include "../../Config/pinout.h"

// Function prototypes
#include "./prototypes.h"

// System Control
#include "../system/control.cpp"
#include "../system/pinconfigs.cpp"

// Components
#include "../components/Heating.cpp"
#include "../components/Sampling.cpp"
#include "../components/StepperControl.cpp"
#include "../components/StepperPump.cpp"
#include "../components/StepperVertical.cpp"
#include "../components/StepperWheel.cpp"

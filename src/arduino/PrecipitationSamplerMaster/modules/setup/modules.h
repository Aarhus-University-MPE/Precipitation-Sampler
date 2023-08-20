#pragma once

// Internal Libraries
#include <Arduino.h>
#include <EEPROM.h>
#include <TimeLib.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// External Libraries
#include <DS3231.h>  // Real-time Clock
#include <HX711.h>   // Load Cell
#include <SD.h>

// Function prototypes
#include "./prototypes.h"

// Tools
#include "../tools/generalFunctions.h"

// Config
#include "../../Config/Constants.h"
#include "../../Config/Pinout.h"
#include "../../Config/memory.h"

// System Control
#include "../system/control.cpp"
#include "../system/pinconfigs.cpp"

// Components
#include "../Components/DataRecorder.cpp"
#include "../Components/Loadcells.cpp"
#include "../Components/Precipitation.cpp"
#include "../Components/Rotiny.cpp"
#include "../Components/SDCard.cpp"
#include "../Components/Sampling.cpp"
#include "../Components/rtc.cpp"
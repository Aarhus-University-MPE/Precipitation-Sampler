#pragma once

#include "../modules/setup/modules.h"

// ------------------------------------------------------------ //
//                           System                             //
// ------------------------------------------------------------ //

#define SYSTEM_VERSION     "0.0.1"
#define ANALOG_HIGH        512

// ------------------------------------------------------------ //
//                       Heating system                         //
// ------------------------------------------------------------ //

#define TEMP_PERIOD        1000
#define TEMP_TARGET        20.0  // °C
#define TEMP_HYSTERESE     2.5   // °C +/-
#define TEMP_MIN           15.0  // °C

// TODO: Configure durations
#define HEATING_DURATION   30000  // ON Period (30 sec) to avoid running heating elements too hot
#define HEATING_TIMEOUT    30000  // OFF Period (30 sec) to avoid running heating elements too hot

// ------------------------------------------------------------ //
//                          STEPPERS                            //
// ------------------------------------------------------------ //

// SAMPLEWHEEL STEPPER          1/16 steps  (3200 steps/rev)
#define WHEEL_MAX_SPEED    500
#define WHEEL_ACC          100

// PUMP STEPPER                 1/4 steps   (800 steps/rev), approximately 0.5 mL/rev
#define PUMP_MAX_SPEED     300
#define PUMP_ACC           100
#define PUMP_SAMPLING_END  3200   // How many steps to do make a sample (3200 approximately 2mL)    TODO: Verify
#define PUMP_PURGE         13000  // How many steps to do a full purge (13000 approximately 8,125 mL)     TODO: Verify
#define FINAL_PURGE_COUNT  5      // Amount of purges done after a sample  TODO: Verify

// VERTICAL STEPPER             1/16 steps  (3200 steps/rev)
#define VERTICAL_MAX_SPEED 300
#define VERTICAL_ACC       100
#define VERTICAL_CLEARING  200  // How many steps to be clear of needles  TODO: Verify

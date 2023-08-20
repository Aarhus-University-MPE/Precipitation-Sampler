/*
  Ice Nucleation Controller (Field Version) system pinout
  Naming pattern (all uppercase):
  P   + <I:input, T: interrupt input, A:analog input, O:output, P:pwm output>_
    + <general part name>_
    + <purpose>_
    + <where applicable: left, right, top, bottom, position etc...>
  Mads Rosenhøj Jeppesen
  Aarhus University
  2023
*/

#pragma once

#include "../modules/setup/modules.h"

// ------------------------------------------------------------ //
//                 Arduino/Arduino communication                //
// ------------------------------------------------------------ //

#define PO_ARDUINO_COM     2  // Communication from Slave to master

// ------------------------------------------------------------ //
//                     Stepper Controllers                      //
// ------------------------------------------------------------ //

#define PO_WHEEL_STP       3  // Sample Wheel stepper-step signal
#define PO_STEPPER_EN      4  // Stepper enable signal to all steppers
#define PO_VERTICAL_STP    5  // Vertical stepper-step signal
#define PO_PUMP_STP        6  // Pump stepper-step signal
#define PO_VERTICAL_DIR    7  // Vertical stepper direction signal

// ------------------------------------------------------------ //
//                        Heat Elements                         //
// ------------------------------------------------------------ //

#define PO_HEAT_FUNNEL     9   // Output signal to turn on funnel heating
#define PO_HEAT_PUMP       10  // Output signal to turn on pump heating

// ------------------------------------------------------------ //
//                     Mechanical switches                      //
// ------------------------------------------------------------ //

#define PI_SWITCH_UPPER    13  // Sample wheel encoding switch (Sample hole)
#define PI_SWITCH_LOWER    11  // Sample wheel encoding switch (Flush hole)
#define PI_SWITCH_VERTICAL 12  // Vertical limit switch

// ------------------------------------------------------------ //
//                      Temp. sensors                           //
// ------------------------------------------------------------ //

#define PA_TEMP_FUNNEL     14  // Temperature sensor for the funnel
#define PA_TEMP_PUMP       15  // Temperature sensor for the Pump

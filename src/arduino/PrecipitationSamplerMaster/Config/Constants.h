#pragma once

#include "../modules/setup/modules.h"

// ------------------------------------------------------------ //
//                             SYSTEM                           //
// ------------------------------------------------------------ //

#define ANALOG_HIGH             512

// ------------------------------------------------------------ //
//                              LID                             //
// ------------------------------------------------------------ //

#define LID_OPEN_DURATION       25000  // milliseconds spent opening lid TODO: Verify
#define LID_SMALLOPEN_DURATION  2500   // milliseconds spent opening lid TODO: Verify

// ------------------------------------------------------------ //
//                   PRECIPITATION DETECTION                    //
// ------------------------------------------------------------ //

#define DETECT_DURATION         1000
#define DETECT_PERIOD           20
#define DETECT_COUNT            15   // number of hits required with sample duration to trigger TODO: Verify
#define DETECT_VALUE_MIN        100  // trigger level TODO: Verify

// ------------------------------------------------------------ //
//                           SAMPLING                           //
// ------------------------------------------------------------ //

#define LOADCELL_FAILURE_MAX    3      // Number of times Loadcell can fail to increase in
#define COLLECTION_TIMEOUT      60000  // Collection timeout duration

#define SAMPLE_FAILSAFE         true          // set false to disable Sample failsafe
#define SAMPLE_FAILSAFE_TIMEOUT 2600000000UL  // Failsafe Timeout, will force collection after given duration (maximum 4,294,967,295 ms = 49,7 days)

#define WAKEUP_COMMAND_DURATION 1000  // Duration for wakeup command
#define ACKNOWLEDGE_TIMEOUT     1000  // Time to wait for acknowledge from slave during sampling
#define WAKEUP_ATTEMPTS_MAX     5     // Max number of attempts to wake slave during sampling

// ------------------------------------------------------------ //
//                           LOAD CELL                          //
// ------------------------------------------------------------ //

#define LOADCELL_UPDATE_PERIOD  1000
#define LOADCELL_INCREASE_MIN   10
#define LOADCELL_FULL_MIN       100  // Minimum level required for 'full' funnel

// ------------------------------------------------------------ //
//                        REAL-TIME CLOCK                       //
// ------------------------------------------------------------ //

#define UNIX_WEEK               604800UL
#define UNIX_3HOURS             10800UL
#define UNIX_15MIN              900UL
#define UNIX_5MIN               300UL

#define MILLIS_WEEK             604800000UL

/*
// Alarm - Long time (TimeSpan( Days, Hours, Minutes, Seconds))
uint8_t sleepLongDays = 14;
uint8_t sleepLongHours = 0;
uint8_t sleepLongMinutes = 0;
uint8_t sleepLongSeconds = 0;

// Alarm - Short time
uint8_t sleepShortDays = 0;
uint8_t sleepShortHours = 2;
uint8_t sleepShortMinutes = 0;
uint8_t sleepShortSeconds = 0;

// Alarm - Sampling time
uint8_t sleepSamplingDays = 0;
uint8_t sleepSamplingHours = 4;
uint8_t sleepSamplingMinutes = 0;
uint8_t sleepSamplingSeconds = 0;
*/
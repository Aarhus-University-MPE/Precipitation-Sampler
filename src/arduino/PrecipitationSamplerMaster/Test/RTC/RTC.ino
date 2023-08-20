/*
  Configure RTC timestamp (in UNIX units)
  Get current timestamp in UNIX units at:
    https://www.unixtimestamp.com/
*/

#include <DS3231.h>
#include <Wire.h>

// Setup clock
DS3231 myRTC;

void setup() {
  // Begin I2C communication
  Wire.begin();

  // Set the DS3231 clock mode to 24-hour
  myRTC.setClockMode(false);  // false = not using the alternate, 12-hour mode

  // Set the clock to an arbitrarily chosen time of
  // 00:00:00 midnight the morning of January 1, 2020
  // using a suitable Unix-style timestamp
  myRTC.setEpoch(1640995200);
}

void loop() {
}

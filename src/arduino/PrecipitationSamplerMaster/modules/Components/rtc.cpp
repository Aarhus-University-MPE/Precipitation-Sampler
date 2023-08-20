#pragma once

#include "../setup/modules.h"

/*
  DS3231 Real time Clock
*/

DS3231 myRTC;

bool century = false;
bool h12Flag;
bool pmFlag;
bool alarmDayIsDay = false;  // using date of month

// Initialize Real-time CLock
void InitializeRTC() {
  Wire.begin();

  myRTC.setClockMode(false);  // false = not using the alternate, 12-hour mode

  DisableAlarm2();
}

// Configures filename to include MM DD HH
void GetTimeStamp(char* fileName) {
  char tempArray[3];
  int month = HexToHour(myRTC.getMonth(century));
  int date  = HexToHour(myRTC.getDate());
  int hour  = HexToHour(myRTC.getHour(h12Flag, pmFlag));

  // MM
  itoa(month, tempArray, 10);
  if (month < 10) {
    fileName[2] = '0';
    fileName[3] = tempArray[0];
  } else {
    fileName[2] = tempArray[0];
    fileName[3] = tempArray[1];
  }

  // DD
  itoa(date, tempArray, 10);
  if (date < 10) {
    fileName[4] = '0';
    fileName[5] = tempArray[0];
  } else {
    fileName[4] = tempArray[0];
    fileName[5] = tempArray[1];
  }

  // HH
  itoa(hour, tempArray, 10);
  if (hour < 10) {
    fileName[6] = '0';
    fileName[7] = tempArray[0];
  } else {
    fileName[6] = tempArray[0];
    fileName[7] = tempArray[1];
  }
}

// Completely disable alarm 2 to prevent waking system unintentionally
void DisableAlarm2() {
  byte alarmMinute = 0xFF;        // a value that will never match the time
  byte alarmBits   = 0b01100000;  // Alarm 2 when minutes match, i.e., never

  // Upload the parameters to prevent Alarm 2 entirely
  myRTC.setA2Time(
      0, 0, alarmMinute,
      alarmBits, alarmDayIsDay, h12Flag, pmFlag);
  // disable Alarm 2 interrupt
  myRTC.turnOffAlarm(2);
  // clear Alarm 2 flag
  myRTC.checkIfAlarm(2);
}

// Turn off Alarm 1
void DisableAlarm() {
  myRTC.turnOffAlarm(1);
  myRTC.checkIfAlarm(1);
}

// Set an alarm for a given duration
void SetAlarm(uint32_t duration) {
  DateTime alarmDT = RTClib::now();
  // extract the DateTime values as a timestamp
  uint32_t nextAlarm = alarmDT.unixtime();
  nextAlarm += duration;
  // update the DateTime with the new timestamp
  alarmDT = DateTime(nextAlarm);

  byte alarmBits = 0b00000000;  // Alarm 1 date, h, m, s match

  // disable Alarm 1 interrupt
  myRTC.turnOffAlarm(1);

  // Clear Alarm 1 flag
  myRTC.checkIfAlarm(1);

  // Upload parameters of Alarm 1
  myRTC.setA1Time(
      alarmDT.day(), alarmDT.hour(), alarmDT.minute(), alarmDT.second(),
      alarmBits, alarmDayIsDay, h12Flag, pmFlag);

  // enable Alarm 1 interrupts
  myRTC.turnOnAlarm(1);
  // clear Alarm 1 flag again after enabling interrupts
  myRTC.checkIfAlarm(1);
}

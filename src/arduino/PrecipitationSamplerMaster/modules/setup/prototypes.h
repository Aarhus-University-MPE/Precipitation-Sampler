#pragma once

#include "./modules.h"

// System
void SystemEnablePrimary();
void InitializePins();
void Sleep(uint32_t duration);

// Master
void ResetSample();
uint8_t GetSampleNumber();

// Data Recorder
void InitializeLoggingFile();
void CancelLoggingFile();
void ProcessStartLoggingFile();
void ProcessEndLoggingFile();

// Lid Motor Control
bool LidHome();
bool LidMoveHome();
bool LidMoveOpen();
void LidStop();

// DS3231 - RTC
void InitializeRTC();
void Sleep();
void SetAlarm();
void SetAlarmLong();
void SetAlarmShort();
void WakeISR();
void GetTimeStamp(char *fileName);

// Alarm timers
void SetAlarm(uint32_t duration);
void DisableAlarm();
void DisableAlarm2();

// Load Cell
void InitializeLoadcell();
void TareLoadcell();
bool LoadcellIncrease();
bool LoadcellChange();

// SD-Card
void InitializeSDReader();
void SeperateDate();

void GetStartDate();
void WriteDate();
void processDate();
bool SDReaderStatus();

// SD Reader
void SDDelete(char fileName[]);
void SDCreate(char fileName[]);
void appendCharArray(char *s, char c);
void appendCsv(char *s);
void printDirectory(File dir, int numTabs);

void AppendToData(char *dataInput, bool endLine);
void AppendToData(char *dataInput);
void AppendToData(uint8_t *dataInput, uint8_t size, bool endLine);
void AppendToData(uint8_t *dataInput, uint8_t size);

// SD Write Steam (Continuous writing to same focument)
void SDWriteStream(char fileNameOrData[], bool customFileEnd);
void SDWriteStream(char fileNameOrData[]);
void SDWriteStream(uint8_t data[], uint8_t size, bool customFileEnd);
void SDWriteStream(uint8_t data[], uint8_t size);
void SDWriteStreamNewLine();
void SDOpenWriteStream(char fileName[], bool customEndLine);
void SDQuit();

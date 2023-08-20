/*
  Local storage protocols

  Mads Rosenhøj Jepepsen
  Aarhus University
  2022
*/

#pragma once
#include <SD.h>

#include "../setup/modules.h"

File activeWriteFile;
bool sdStatus = false;

// Initialize SD card reader module.
void InitializeSDReader() {
  sdStatus = SD.begin(PO_SD_CS);
  if (sdStatus) {
    sdStatus = SD.mkdir("data");
  }
}

// Terminate SD reader module
void TerminateSDReader() {
  SD.end();
}

// Returns true if SDreader is functional
bool SDReaderStatus() {
  return sdStatus;
}

// Delete file on SD card
void SDDelete(char fileName[]) {
  if (!SDReaderStatus()) return;
  if (!SD.exists(fileName)) return;
  SD.remove(fileName);
}

// Create empty file on SD card
void SDCreate(char fileName[]) {
  if (!SDReaderStatus()) return;

  appendCsv(fileName);

  File file = SD.open(fileName, FILE_WRITE);
}

/*
  Initializes file write stream
  First run opens file with name, consecutive runs appends data to opened file
  When complete run SDQuit() to close write stream
*/
void SDWriteStream(char fileNameOrData[], bool customFileEnd) {
  if (!SDReaderStatus()) return;

  if (activeWriteFile) {
    activeWriteFile.write(fileNameOrData);
  } else {
    SDOpenWriteStream(fileNameOrData, customFileEnd);
  }
}

/*
  Initializes file write stream
  First run opens file with name, consecutive runs appends data to opened file
  When complete run SDQuit() to close write stream
*/
void SDWriteStream(char fileNameOrData[]) {
  SDWriteStream(fileNameOrData, false);
}

/*
  Write binary data to file stream
  When complete run SDQuit() to close write stream
*/
void SDWriteStream(uint8_t data[], uint8_t size, bool customFileEnd) {
  if (!SDReaderStatus()) return;
  if (!activeWriteFile) return;

  activeWriteFile.write(data, size);
}

/*
  Write binary data to file stream
  When complete run SDQuit() to close write stream
*/
void SDWriteStream(uint8_t data[], uint8_t size) {
  SDWriteStream(data, size, false);
}

/*
  Initializes file write stream
  First run opens file with name, consecutive runs appends data to opened file
  When complete run SDQuit() to close write stream
*/
void SDWriteStreamNewLine() {
  if (!activeWriteFile) return;

  activeWriteFile.write('\r');
  activeWriteFile.write('\n');
}

void SDOpenWriteStream(char fileName[], bool customEndLine) {
  if (!customEndLine) {
    appendCsv(fileName);
  }

  // TODO: remove?
  if (!SD.exists(fileName)) {
    activeWriteFile = SD.open(fileName, FILE_WRITE);
    if (!activeWriteFile) return;
  }

  else {
    activeWriteFile = SD.open(fileName, FILE_WRITE);
  }
}

// Closes current active file write stream
void SDQuit() {
  activeWriteFile.close();
}

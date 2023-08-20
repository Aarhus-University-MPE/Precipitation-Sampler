char fileLocationData[22];
unsigned long dataIndex = 0;
File dataFile;

// Append data to the current data file
void AppendToData(char *dataInput, bool endLine) {
  if (!SDReaderStatus()) return;
  SDWriteStream(fileLocationData, true);
  SDWriteStream(dataInput);
  if (endLine) SDWriteStreamNewLine();
  SDQuit();
}

// Append dat without lineend
void AppendToData(char *dataInput) {
  AppendToData(dataInput, false);
}

// Append data to the current data file
void AppendToData(uint8_t *dataInput, uint8_t size, bool endLine) {
  if (!SDReaderStatus()) return;
  SDWriteStream(fileLocationData, true);
  SDWriteStream(dataInput, size);
  if (endLine) SDWriteStreamNewLine();
  SDQuit();
}

// Append data without lineend
void AppendToData(uint8_t *dataInput, uint8_t size) {
  AppendToData(dataInput, size, false);
}

// Append Package Identifier
void AppendPackageIdentifierToData() {
  uint8_t identifierData[1];
  identifierData[0] = 0xA;

  AppendToData(identifierData, 1, false);
}

// Append and increment
void AppendIndexToData() {
  uint8_t indexData[4];
  // Convert index to binary
  for (uint8_t i = 0; i < 4; i++) {
    indexData[i] = ((dataIndex >> (8 * i)) & 0XFF);
  }

  dataIndex++;
  AppendToData(indexData, 4, false);
}

// Add current timestamp
void TimeStampData() {
  uint8_t timeStampData[4];
  unsigned long timeStamp = (unsigned long)now();

  // Convert timestamp to binary
  for (uint8_t i = 0; i < 4; i++) {
    timeStampData[i] = ((timeStamp >> (8 * i)) & 0XFF);
  }

  AppendToData(timeStampData, 4, true);
}

// Create logging file (##MMDDHH.csv)
void InitializeLoggingFile() {
  char folder[8]   = "/data/";
  char fileName[9] = "##MMDDHH";  // 01052012 -> Sample 01, 20th of May 12:00

  // Add Sample Number to file name
  char tempArray[3];
  itoa(GetSampleNumber(), tempArray, 10);
  if (GetSampleNumber() < 10) {
    fileName[0] = '0';
    fileName[1] = tempArray[0];
  } else {
    fileName[0] = tempArray[0];
    fileName[1] = tempArray[1];
  }

  // Get current time for data name
  GetTimeStamp(fileName);

  // Clear file names
  memset(fileLocationData, 0, 22);

  // Combine folder, filename and format
  strcpy(fileLocationData, folder);
  strcat(fileLocationData, fileName);

  // Create data file
  SDCreate(fileLocationData);

  char heading[9] = "Sample: ";

  // Initialize data file
  AppendToData(heading, false);
  AppendToData(GetSampleNumber(), true);
  TimeStampData();
}

// Timestamp and indicate sample processing begun
void ProcessStartLoggingFile() {
  char input[22] = "Sample Process Begun";
  AppendToData(input, true);
  TimeStampData();
}

// Timestamp and indicate sample processing ended
void ProcessEndLoggingFile() {
  char input[22] = "Sample Process succes";
  AppendToData(input, true);
  TimeStampData();
}

// Timestamp and indicate a cancelled collection
void CancelLoggingFile() {
  char input[18] = "Sample CANCELLED";
  AppendToData(input, true);
  TimeStampData();
}
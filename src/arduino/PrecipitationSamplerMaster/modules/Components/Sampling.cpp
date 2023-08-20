/*
  Primary Sampling Functions for Precipitation Sampler Master Module

  By:
    Mads Rosenhøj Jeppesen
    Aarhus University
    2023
*/

uint8_t sampleState  = 0;
uint8_t sampleNumber = 0;

unsigned long millisCollectionStarted = 0;
unsigned long lastMillisSample        = 0;

uint8_t loadcellFailure = 0;

// Returns current Sample Number
uint8_t GetSampleNumber() {
  return sampleNumber;
}

// Resets sampling process (Run on system boot-up)
void ResetSample() {
  sampleState  = 0;
  sampleNumber = 0;
}

// Initialize Sampling
void StartSample() {
  sampleState = 0;
}

// Send wake command to Slave for
void SendWakeCommand() {
  // Set wake pin to high output
  pinMode(PI_ARDUINO_COM, OUTPUT);
  digitalWrite(PI_ARDUINO_COM, true);

  // Hold wake-signal for given duration
  delay(WAKEUP_COMMAND_DURATION);

  // Set pin to input awaiting acknowledge
  digitalWrite(PI_ARDUINO_COM, false);
  pinMode(PI_ARDUINO_COM, INPUT);

  // Allow pin to change
  delay(100);
}

// Await acknowledge command from Slave (SIGNAL HIGH)
bool AwaitAcknowledge() {
  bool acknowledgeReceived       = false;
  unsigned long millisStartAwait = millis();

  // Wait for acknowledge
  while (millis() - millisStartAwait < ACKNOWLEDGE_TIMEOUT && !acknowledgeReceived) {
    acknowledgeReceived = digitalRead(PI_ARDUINO_COM);
    delay(100);
  }

  return acknowledgeReceived;
}

// Await completion command from Slave (SIGNAL LOW)
bool AwaitCompletion() {
  bool complitionReceived        = false;
  unsigned long millisStartAwait = millis();

  // Wait for acknowledge
  while (millis() - millisStartAwait < ACKNOWLEDGE_TIMEOUT && !complitionReceived) {
    complitionReceived = !digitalRead(PI_ARDUINO_COM);
    delay(100);
  }

  return complitionReceived;
}

// Send wake command and return acknowledge
bool WakeSlave() {
  SendWakeCommand();
  return AwaitAcknowledge();
}

// Stop Sample collection
void StopSample() {
  sampleState = 0;
}

// Sample collection and process complete
void CompleteSample() {
  lastMillisSample = millis();
  ProcessEndLoggingFile();

  StopSample();
}

// Start a sample collection
void StartCollection() {
  TareLoadcell();  // Re-zero load cells

  // Increment Sample Number
  sampleNumber++;

  // Configure data file
  InitializeLoggingFile();

  millisCollectionStarted = millis();
  loadcellFailure         = 0;
}

// Cancel collection due to timeout/insufficient rain
void CancelCollection() {
  CancelLoggingFile();
  sampleNumber--;
}

// Communicate to slave to save sample
void SaveSample() {
  uint8_t wakeupAttempts = 0;
  bool wakeupSuccess     = false;

  // Attempt to wakeup slave
  while (wakeupAttempts < WAKEUP_ATTEMPTS_MAX && !wakeupSuccess) {
    wakeupSuccess = WakeSlave();
    if (!wakeupSuccess) wakeupAttempts++;
  }

  // Received Acknowledge?
  if (wakeupSuccess) {
    // Stamp data file indicating successfull save begun
    ProcessStartLoggingFile();
  } else {
    // Failed to wake slave CRITICAL TODO: How to handle?
    CancelCollection();
  }
}
// Returns current sample state
uint8_t GetSampleState() {
  return sampleState;
}

// Returns true if collection timed out
bool CollectionTimeout() {
  return millis() - millisCollectionStarted > COLLECTION_TIMEOUT;
}

// Returns true if time since last sample was collected is above a timeout (Failsafe to ensure at least some samples)
bool SampleFailsafeTimeout() {
  if (!SAMPLE_FAILSAFE) return false;  // Ignore failsafe if flag not set

  return millis() - lastMillisSample > SAMPLE_FAILSAFE_TIMEOUT;
}

// Primary collection process
bool CollectionProcess() {
  // Load cell full?
  if (LoadcellFull()) return true;

  // Ignore time and detection constraints if SampleFailsafeTimeout is active
  if (SampleFailsafeTimeout()) return false;

  // Collection timed out?
  if (CollectionTimeout()) CancelCollection();

  // Load cell value not increased?
  if (!LoadcellIncrease()) {
    loadcellFailure++;
    if (loadcellFailure > LOADCELL_FAILURE_MAX) CancelCollection();
  }

  return false;
}

// Handle sleeping during sampling process
void SampleSleep() {
  switch (sampleState) {
    case 0:  // No Precipitation detected and no forced sample (Sample Failsafe Timeout)
      // long sleep
      if (millis() - lastMillisSample < MILLIS_WEEK) {  // Sleep for a week if sample was collected less than a week ago
        Sleep(UNIX_WEEK);
      } else {
        Sleep(UNIX_3HOURS);
      }
      break;

    case 3:  // Collection Process, wait for funnel to fill up
      // For failsafe slowly increment sleep duration
      if (SampleFailsafeTimeout()) {
      } else {
        Sleep(UNIX_5MIN);
      }
      break;

    case 6:  // Sample being saved, wait for slave to finish processing sample
      Sleep(UNIX_5MIN);
      break;

    default:
      // Don't sleep
      break;
  }
}

// Primary Sampling Process
void SamplingProcess() {
  switch (sampleState) {
    case 0:  // Check precipitation detection or Forced sample (Sample Failsafe Timout)
      if (DetectPrecipitation() || SampleFailsafeTimeout()) sampleState++;
      break;

    case 1:  // Open Lid and Start Sample
      if (LidMoveOpen()) sampleState++;
      break;

    case 2:  // Start Collection Process
      StartCollection();
      sampleState++;
      break;

    case 3:  // Check loadcell values/system timout and sleep
      if (CollectionProcess()) sampleState++;
      break;

    case 4:  // Close lid
      if (LidMoveHome()) sampleState++;
      break;

    case 5:  // Communicate to slave to save sample
      SaveSample();
      break;

    case 6:  // Await finished sample processing complete
      if (AwaitCompletion()) sampleState++;
      break;

    case 7:  // Sample finished
      CompleteSample();
      break;

    default:
      sampleState = 0;
      break;
  }

  // Return to sleep during specific samples
  SampleSleep();
}
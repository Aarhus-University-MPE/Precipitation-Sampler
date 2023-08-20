/*
  Lid motor controller, utilizing a Rotiny motor
  On startup will home system and then continuously open and close Lid

  Mads Rosenhøj Jepepsen
  Aarhus University
  2022
*/

#define PO_LID_OPEN            5      // Open signal pin
#define PO_LID_CLOSE           6      // Close signal pin
#define PI_SWITCH_LID          14     // Limitswitch for "Lid Closed"
#define LID_SMALLOPEN_DURATION 2500   // milliseconds spent opening lid TODO: Verify
#define LID_OPEN_DURATION      25000  // milliseconds spent opening lid TODO: Verify
#define ANALOG_HIGH            512

void setup() {
  pinMode(PO_LID_CLOSE, OUTPUT);
  pinMode(PO_LID_OPEN, OUTPUT);
  pinMode(PI_SWITCH_LID, INPUT);

  while (!LidHome()) {
    ;
  }
}

void loop() {
  delay(1000);

  // Open lid
  while (!LidMove(true);) {
  }

  delay(1000);

  // Close lid
  while (!LidMove(false);) {
  }
}

unsigned long motorStartMillis = 0;
uint8_t homingState            = 0;

// Homing Stepper Switch
bool ReadHomeSwitch() {
  return analogRead(PI_SWITCH_LID) >= ANALOG_HIGH;
}

// Move Lid motor
void LidMove(bool open) {
  if (open && digitalRead(PO_LID_OPEN)) return;
  if (!open && digitalRead(PO_LID_CLOSE)) return;

  if (open) {
    digitalWrite(PO_LID_CLOSE, false);
    digitalWrite(PO_LID_OPEN, true);
  } else {
    digitalWrite(PO_LID_OPEN, false);
    digitalWrite(PO_LID_CLOSE, true);
  }

  // Set Start timestamp
  motorStartMillis = millis();
}

// Stop Lid Motor
void LidStop() {
  digitalWrite(PO_LID_CLOSE, false);
  digitalWrite(PO_LID_OPEN, false);
}

// Rotate towards home position
bool LidMoveHome() {
  if (ReadHomeSwitch()) {
    LidStop();
    return true;
  }

  LidMove(false);
  return false;
}

// Rotate towards open position
bool LidMoveOpen() {
  if (millis() - motorStartMillis > LID_OPEN_DURATION) {
    LidStop();
    return true;
  }

  LidMove(true);
  return false;
}

// Rotate towards open position for a short duration
bool LidMoveOpenSmall() {
  if (millis() - motorStartMillis > LID_SMALLOPEN_DURATION) {
    LidStop();
    return true;
  }

  LidMove(true);
  return false;
}

// Homing procedure
bool LidHome() {
  switch (homingState) {
    case 0:  // Checkif already at home position
      if (ReadHomeSwitch()) {
        homingState++;
      } else {  // Skip moving clear if not at home position
        homingState += 2;
      }
      break;

    case 1:  // Open Slightly
      if (LidMoveOpenSmall()) homingState++;
      break;

    case 2:  // Move towards home position
      if (LidMoveHome()) {
        homingState = 0;
        return true;
      }
      break;

    default:
      break;
  }

  return false;
}

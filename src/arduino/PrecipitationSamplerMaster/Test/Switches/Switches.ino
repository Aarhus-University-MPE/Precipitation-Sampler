#define PI_SWTCH_LID 14  // Limitswitch for "Lid Closed"

int LID;
int prevLID = 0;

unsigned long lastMillis;

void setup() {
  Serial.begin(9600);
  pinMode(PI_SWTCH_LID, INPUT);
  Serial.println("Program Startet");
}

void loop() {
  if (millis() - lastMillis >= 200) {
    lastMillis = millis();
    LID        = digitalRead(PI_SWTCH_LID);
  }

  if (prevLID != LID) {
    prevLID = LID;
    Serial.print("Lid:   ");
    Serial.println(LID);
  }
}

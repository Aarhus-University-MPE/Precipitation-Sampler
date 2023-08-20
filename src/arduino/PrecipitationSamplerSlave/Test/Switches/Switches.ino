#define PI_SWTCH_UPPER  13  // Sample wheel encoding switch (Sample hole)
#define PI_SWTCH_LOWER  11  // Sample wheel encoding switch (Flush hole)
#define PI_SWTCH_HEIGHT 12  // Height limit switch

int Upper;
int Lower;
int Height;
int prevHeight = 0;
int prevUpper  = 0;
int prevLower  = 0;

unsigned long lastMillis;

void setup() {
  Serial.begin(9600);
  pinMode(PI_SWTCH_UPPER, INPUT);
  pinMode(PI_SWTCH_LOWER, INPUT);
  pinMode(PI_SWTCH_HEIGHT, INPUT);
  Serial.print("Program Startet");
}

void loop() {
  if (millis() - lastMillis >= 500) {
    lastMillis = millis();
    Upper      = digitalRead(PI_SWTCH_UPPER);
    Lower      = digitalRead(PI_SWTCH_LOWER);
    Height     = digitalRead(PI_SWTCH_HEIGHT);
  }

  if (prevHeight != Height) {
    prevHeight = Height;
    Serial.print("HEIGHT:   ");
    Serial.println(Height);
  }

  if (prevUpper != Upper) {
    prevUpper = Upper;
    Serial.print("Upper:   ");
    Serial.println(Upper);
  }

  if (prevLower != Lower) {
    prevLower = Lower;
    Serial.print("Lower:   ");
    Serial.println(Lower);
  }
}

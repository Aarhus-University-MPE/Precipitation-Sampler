#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN  = 17;

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale();
  scale.tare();

  Serial.println("Place weight on scale");
  while (!Serial.available()) {
  };

  float x = scale.get_units(10);
  Serial.println(x);
}

void loop() {
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(PA_DIST_SENSE));
  delay(20);
}

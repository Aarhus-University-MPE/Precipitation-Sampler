#define PA_TEMP_FUNNEL 14  // Temperature sensor for the funnel
#define PA_TEMP_PUMP   15  // Temperature sensor for the Pump
#define TEMP_PERIOD    1000

unsigned long lastMillisTempUpdate = 0;

float currentTempFunnel = 0;
float currentTempPump   = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Program Started");
}

void loop() {
  UpdateTemperatures();
}

// Update system temperature readings
void UpdateTemperatures() {
  if (millis() - lastMillisTempUpdate < TEMP_PERIOD) return;

  lastMillisTempUpdate = millis();
  currentTempFunnel    = ReadTemperature(PA_TEMP_FUNNEL);
  currentTempPump      = ReadTemperature(PA_TEMP_PUMP);

  Serial.print(F("Funnel: "));
  Serial.println(currentTempFunnel);

  Serial.print(F("Pump: "));
  Serial.println(currentTempPump);

  Serial.println();
}

// Convert sensor value to Degrees Celcius
float Analog2Celcius(int Reading) {
  float tempCelcius = (Reading / 1024.0) * 5.0;     // Assuming a 5V reference voltage
  tempCelcius       = (tempCelcius - 0.5) * 100.0;  // Assuming a 10mV/°C temperature sensor

  return tempCelcius;
}

// Update system temperatures
float ReadTemperature(int temperaturePin) {
  int TSensor       = analogRead(temperaturePin);
  float temperature = Analog2Celcius(TSensor);

  return temperature;
}
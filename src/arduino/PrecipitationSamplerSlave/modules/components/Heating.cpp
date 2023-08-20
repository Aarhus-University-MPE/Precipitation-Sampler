#pragma once

#include "../setup/modules.h"

unsigned long lastMillisTempUpdate    = 0;
unsigned long lastMillisTempOnFunnel  = 0;
unsigned long lastMillisTempOffFunnel = 0;
unsigned long lastMillisTempOnPump    = 0;
unsigned long lastMillisTempOffPump   = 0;

float currentTempFunnel = 0;
float currentTempPump   = 0;

// Turn off all heating
void DisableHeating() {
  lastMillisTempOffFunnel = millis();
  lastMillisTempOffPump   = millis();

  digitalWrite(PO_HEAT_FUNNEL, false);
  digitalWrite(PO_HEAT_PUMP, false);
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

// Update system temperature readings
void UpdateTemperatures() {
  if (millis() - lastMillisTempUpdate < TEMP_PERIOD) return;

  lastMillisTempUpdate = millis();
  currentTempFunnel    = ReadTemperature(PA_TEMP_FUNNEL);
  currentTempPump      = ReadTemperature(PA_TEMP_PUMP);
}

// Returns true if current temperature is above minimum (Target Temp - Hysteresis)
bool HeatingSufficient() {
  return (currentTempPump > TEMP_TARGET - TEMP_HYSTERESE && currentTempFunnel > TEMP_TARGET - TEMP_HYSTERESE);
}

// Funnel Heating Hysteresis Control
void HeaterFunnel() {
  // Currently Heating
  if (digitalRead(PO_HEAT_FUNNEL)) {
    // Temp Above Target+Hysteresis or ON-period above maximum duration
    if (currentTempFunnel > TEMP_TARGET + TEMP_HYSTERESE || millis() - lastMillisTempOnFunnel > HEATING_DURATION) {
      digitalWrite(PO_HEAT_FUNNEL, false);
      lastMillisTempOffFunnel = millis();
    }
  }

  // Not currently Heating
  else {
    // Temperature below Target-Hysteresis and OFF-period above minimum duration
    if (currentTempFunnel < TEMP_TARGET - TEMP_HYSTERESE && millis() - lastMillisTempOffFunnel > HEATING_TIMEOUT) {
      digitalWrite(PO_HEAT_FUNNEL, true);
      lastMillisTempOnFunnel = millis();
    }
  }
}

// Pump Heating Hysteresis Control
void HeaterPump() {
  // Currently Heating
  if (digitalRead(PO_HEAT_PUMP)) {
    // Temp Above Target+Hysteresis or ON-period above maximum duration
    if (currentTempPump > TEMP_TARGET + TEMP_HYSTERESE || millis() - lastMillisTempOnPump > HEATING_DURATION) {
      digitalWrite(PO_HEAT_PUMP, false);
      lastMillisTempOffPump = millis();
    }
  }
  // Not currently Heating
  else {
    // Temperature below Target-Hysteresis and OFF-period above minimum duration
    if (currentTempPump < TEMP_TARGET - TEMP_HYSTERESE && millis() - lastMillisTempOffPump > HEATING_TIMEOUT) {
      digitalWrite(PO_HEAT_PUMP, true);
      lastMillisTempOnPump = millis();
    }
  }
}

// Primary Heating Process, ensures target temperature +/- Hysteresis
void HeatingProcess() {
  UpdateTemperatures();

  HeaterFunnel();
  HeaterPump();
}

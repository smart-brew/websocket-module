#include "tempSensor.hpp"

OneWire oneWire(SENSOR_TEMP_PIN);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors1(&oneWire);

void startTempSensors() {
  // start temperature sensors
  sensors1.begin();
}

float getTemperature(int sensorId) {
  sensors1.requestTemperatures();
  return sensors1.getTempCByIndex(sensorId);
}
#include "tempSensor.hpp"

TempSensor::TempSensor(int pin, String sensorName) {
  sensorPin = pin;
  name = sensorName;
}

void TempSensor::init() {
  oneWire.begin(sensorPin);
  dallasTempSensors.setOneWire(&oneWire);
  dallasTempSensors.begin();

  Serial.println("[temp sensor] ready");
}

String TempSensor::getName() {
  return name;
}

String TempSensor::getCategory() {
  return category;
}

float TempSensor::get() {
  dallasTempSensors.requestTemperatures();
  return dallasTempSensors.getTempCByIndex(0);
}

void TempSensor::getJsonValues(JsonObject& obj) {
  dallasTempSensors.requestTemperatures();
  obj["TEMP"] = dallasTempSensors.getTempCByIndex(0);
}

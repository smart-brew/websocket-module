#include "tempSensor.hpp"

TempSensor::TempSensor(String _name, int pin) {
  sensorPin = pin;
  name = _name;
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

String TempSensor::getStatus() {
  return DEVICE_STATUS[status];
}

float TempSensor::get() {
  dallasTempSensors.requestTemperatures();
  return dallasTempSensors.getTempCByIndex(0);
}

void TempSensor::appendJsonValues(JsonObject& obj) {
  dallasTempSensors.requestTemperatures();

  int count = dallasTempSensors.getDeviceCount();

  for (int i = 0; i < count; i++) {
    obj["temp" + String(i)] = dallasTempSensors.getTempCByIndex(i);
  }
}

void TempSensor::executeFunction(JsonDocument& obj) {}

void TempSensor::abort() {
  status = DEVICE_WAITING;
}
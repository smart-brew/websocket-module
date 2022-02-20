#include "tempLogic.hpp"

TempRegulator::TempRegulator(String deviceName, TempSensor& _tempSensor) {
  tempSensor = &_tempSensor;
  name = deviceName;
}

void TempRegulator::init() {
  tempSensor->init();
  Serial.println("[temp logic] ready");
}

String TempRegulator::getName() {
  return name;
}

String TempRegulator::getCategory() {
  return category;
}

float TempRegulator::get() {
  return tempSensor->get();
}

String TempRegulator::getStatus() {
  return DEVICE_STATUS[status];
}

void TempRegulator::appendJsonValues(JsonObject& obj) {
  updateStatus();

  tempSensor->appendJsonValues(obj);
  obj["regulation_enabled"] = enabled;
}

void TempRegulator::executeFunction(JsonDocument& obj) {
  String instruction = obj["instruction"];

  // SET_TEMPERATURE
  if (instruction.equals("SET_TEMPERATURE") && !obj["param"].isNull()) {
    enabled = true;
    status = DEVICE_IN_PROGRESS;

    tempTarget = obj["param"].as<float>();

    if (get() < tempTarget) {
      tempRaise = true;
    } else {
      tempRaise = false;
    }
  }
}

void TempRegulator::updateStatus() {
  if (status == DEVICE_DONE) {
    status = DEVICE_WAITING;
  }

  float currentTemperature = get();
  if (status == DEVICE_IN_PROGRESS &&
      ((currentTemperature > tempTarget && tempRaise) ||
       (currentTemperature < tempTarget && !tempRaise))) {
    status = DEVICE_DONE;
  }
}

void TempRegulator::abort() {
  status = DEVICE_WAITING;
}
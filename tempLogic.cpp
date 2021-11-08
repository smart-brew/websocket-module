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

void TempRegulator::appendJsonValues(JsonObject& obj) {
  updateStatus();

  tempSensor->appendJsonValues(obj);
  obj["REGULATION_ENABLED"] = enabled;
  obj["STATUS"] = DEVICE_STATUS[status];
}

void TempRegulator::executeFunction(JsonDocument& obj) {
  String instruction = obj["INSTRUCTION"];

  // SET_TEMPERATURE
  if (instruction.equals("SET_TEMPERATURE") && !obj["PARAMS"].isNull()) {
    enabled = true;
    status = DEVICE_IN_PROGRESS;

    tempTarget = obj["PARAMS"].as<float>();

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

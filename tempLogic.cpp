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
  return 0;
}

void TempRegulator::appendJsonValues(JsonObject& obj) {
  tempSensor->appendJsonValues(obj);
  obj["REGULATION_ENABLED"] = enabled;
}

void TempRegulator::executeFunction(JsonDocument& obj) {
  // const char* dev = getName().c_str();
  // Serial.println(dev);
  // if (strcmp(obj["DEVICE"], getName().c_str())) {
  //   Serial.printf("Match ");
  Serial.println(getName());
  // }
}

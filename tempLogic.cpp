#include "tempLogic.hpp"

TempRegulator::TempRegulator(String deviceName) {
  name = deviceName;
}

void TempRegulator::init() {
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
}

void TempRegulator::executeFunction(JsonObject& obj) {}

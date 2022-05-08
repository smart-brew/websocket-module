#include "simpleRelay.hpp"

SimpleRelay::SimpleRelay(String deviceName, String _category, String _instruction, PinEnabler& _pinEnabler) {
  pinEnabler = &_pinEnabler;
  name = deviceName;
  category = _category;
  instruction = _instruction;
}

void SimpleRelay::init() {
  pinEnabler->init();
  Serial.println("[simple relay] ready");
}

String SimpleRelay::getName() {
  return name;
}

String SimpleRelay::getCategory() {
  return category;
}

float SimpleRelay::get() {
  return pinEnabler->getStatus();
}

String SimpleRelay::getStatus() {
  return DEVICE_STATUS[status];
}

void SimpleRelay::appendJsonValues(JsonObject& obj) {
  updateStatus();

  obj["enabled"] = get();
}

void SimpleRelay::executeFunction(JsonDocument& obj) {
  String instructionMaster = obj["instruction"];
  const char* value = obj["params"];

  Serial.println("[simple relay] execute function");

  if (instructionMaster.equals(instruction)) {
    status = DEVICE_IN_PROGRESS;

    if (atof(value)) {
      pinEnabler->enable();
    } else {
      pinEnabler->disable();
    }
  }
}

void SimpleRelay::updateStatus() {
  if (status == DEVICE_DONE) {
    status = DEVICE_WAITING;
  }

  if (status == DEVICE_IN_PROGRESS) {
    status = DEVICE_DONE;
  }
}

void SimpleRelay::abort() {
  status = DEVICE_WAITING;

  pinEnabler->disable();
}
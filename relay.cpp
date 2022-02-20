#include "relay.hpp"

bool RELAY_OPEN = false;

// must be on serial ports only
void startRelay() {
  Serial2.begin(9600, SERIAL_8N1, RELAY_RX, RELAY_TX);
  relayClose();
}

void relayOpen() {
  // open: A0 01 00 A1
  Serial2.write("\xa0\x01");
  Serial2.write(0x00);  // null terminates a string so it has to be sent on its own
  Serial2.write(0xa1);

  RELAY_OPEN = true;
}
void relayClose() {
  // close: A0 01 01 A2
  Serial2.write("\xa0\x01\x01\xa2");

  RELAY_OPEN = false;
}

float RelayModule::get() {
  return RELAY_OPEN;
}

RelayModule::RelayModule(String sensorName) {
  name = sensorName;
}

void RelayModule::init() {
  // startRelay();

  Serial.println("[relay] ready");
}

String RelayModule::getName() {
  return name;
}

String RelayModule::getStatus() {
  return DEVICE_STATUS[status];
}

String RelayModule::getCategory() {
  return category;
}

void RelayModule::appendJsonValues(JsonObject& obj) {
  updateStatus();

  obj["open"] = RELAY_OPEN;
}

void RelayModule::executeFunction(JsonDocument& obj) {
  String instruction = obj["instruction"];

  // OPEN_RELAY
  if (instruction.equals("OPEN_RELAY")) {
    status = DEVICE_IN_PROGRESS;

    relayOpen();
  } else if (instruction.equals("CLOSE_RELAY")) {
    status = DEVICE_IN_PROGRESS;

    relayClose();
  }
}

void RelayModule::abort() {
  status = DEVICE_WAITING;
}

void RelayModule::updateStatus() {
  if (status == DEVICE_DONE) {
    status = DEVICE_WAITING;
  }

  if (status == DEVICE_IN_PROGRESS) {
    status = DEVICE_DONE;
  }
}
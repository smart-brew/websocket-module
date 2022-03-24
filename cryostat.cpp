#include "cryostat.hpp"

Cryostat::Cryostat(String sensorName) {
  name = sensorName;
}

void Cryostat::init() {
  if (serial_bus.available()) {
    serial_bus.begin(baud_rate, SERIAL_8N1);
  }

  Serial.println("[cryostat] ready");
}

String Cryostat::getName() {
  return name;
}

String Cryostat::getStatus() {
  return DEVICE_STATUS[status];
}

String Cryostat::getCategory() {
  return category;
}

void Cryostat::appendJsonValues(JsonObject& obj) {
  updateStatus();

  // obj["cryostat_bath_temp"] = sendCommand(bath_temp_command);

  // The next command should only be sent after 100 ms.
  // delay(100);
  obj["cryostat_working_temp"] = sendCommand(working_temp_command);
}

void Cryostat::executeFunction(JsonDocument& obj) {
  String instruction = obj["instruction"];

  // SET_ANGLE
  if (instruction.equals("SET_TEMPERATURE") && !obj["param"].isNull()) {
    status = DEVICE_IN_PROGRESS;

    Serial.printf("SET_TEMPERATURE %d\n", obj["param"].as<int>());
    setTemperature(obj["param"].as<int>());
  }
}

void Cryostat::abort() {
  status = DEVICE_WAITING;
}

void Cryostat::updateStatus() {
  if (status == DEVICE_DONE) {
    status = DEVICE_WAITING;
  }

  if (status == DEVICE_IN_PROGRESS) {
    status = DEVICE_DONE;
  }
}

String Cryostat::sendCommand(String command) {
  // send command to CF41
  serial_bus.write(command.c_str() + '\x0d');

  // wait for response
  while (serial_bus.available() == 0) {
    delay(50);
  }

  // read response
  String response = serial_bus.readStringUntil('\x0a');
  Serial.printf("[cryostat] response: %s\n", response.c_str());

  return response;
}

void Cryostat::setTemperature(int param) {
  sendCommand(set_temp_command + param);
}
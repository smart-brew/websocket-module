#include "servo.hpp"

float ServoMotor::get() {
  return servo.read();
}

void ServoMotor::write(int angle) {
  servo.write(angle);
}

ServoMotor::ServoMotor(int pin, String sensorName) {
  servoPin = pin;
  name = sensorName;
}

void ServoMotor::init() {
  servo.attach(servoPin);
  servo.write(90);

  Serial.println("[servo] ready");
}

String ServoMotor::getName() {
  return name;
}

String ServoMotor::getStatus() {
  return DEVICE_STATUS[status];
}

String ServoMotor::getCategory() {
  return category;
}

void ServoMotor::appendJsonValues(JsonObject& obj) {
  updateStatus();

  obj["angle"] = servo.read();
}

void ServoMotor::executeFunction(JsonDocument& obj) {
  String instruction = obj["instruction"];

  // SET_ANGLE
  if (instruction.equals("SET_ANGLE") && !obj["param"].isNull()) {
    status = DEVICE_IN_PROGRESS;

    Serial.printf("SET_ANGLE %d\n", obj["param"].as<int>());

    write(obj["param"].as<int>());
  }
}

void ServoMotor::abort() {
  status = DEVICE_WAITING;
}

void ServoMotor::updateStatus() {
  if (status == DEVICE_DONE) {
    status = DEVICE_WAITING;
  }

  if (status == DEVICE_IN_PROGRESS) {
    status = DEVICE_DONE;
  }
}
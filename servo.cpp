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
  obj["angle"] = servo.read();
}

void ServoMotor::executeFunction(JsonDocument& obj) {}

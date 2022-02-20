#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>  // download from: https://github.com/madhephaestus/ESP32Servo

#include "device.hpp"

class ServoMotor : public Device {
 private:
  String name;
  String category = "SERVO";
  int status = DEVICE_WAITING;

  Servo servo;
  int servoPin;

 public:
  void init();
  void abort();
  float get();
  String getName();
  String getCategory();
  String getStatus();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonDocument& obj);

  ServoMotor(int pin, String sensorName);
  void write(int angle);
  void updateStatus();
};

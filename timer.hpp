#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>  // download from: https://github.com/madhephaestus/ESP32Servo

#include "device.hpp"

class Timer : public Device {
 private:
  String name;
  String category = "SYSTEM";

  struct timeval start;
  struct timeval now;
  int32_t length;
  int status = DEVICE_WAITING;

 public:
  void init();
  String getName();
  String getCategory();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonDocument& obj);

  Timer(String timerName);
  int32_t getRemaining();
  void updateStatus();
};

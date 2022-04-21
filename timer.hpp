#pragma once

#include <Arduino.h>

#include "device.hpp"

class Timer : public Device {
 private:
  String name;
  String category = "SYSTEM";
  int status = DEVICE_WAITING;

  struct timeval start;
  struct timeval now;
  int32_t length;

 public:
  void init();
  void abort();
  String getName();
  String getCategory();
  String getStatus();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonDocument& obj);

  Timer(String timerName);
  int32_t getRemaining();
  void updateStatus();
};

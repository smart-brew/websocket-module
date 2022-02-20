#pragma once

#include <Arduino.h>

// === logic ===
#include "tempSensor.hpp"

class TempRegulator : public Device {
 private:
  String name;
  String category = "TEMPERATURE";
  int status = DEVICE_WAITING;

  TempSensor* tempSensor;

  boolean tempRaise = true;
  boolean enabled = false;
  float tempTarget = 0;

 public:
  void init();
  void abort();
  float get();
  String getName();
  String getCategory();
  String getStatus();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonDocument& obj);

  TempRegulator(String deviceName, TempSensor& _tempSensor);
  void updateStatus();
};

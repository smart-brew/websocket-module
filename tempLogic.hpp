#pragma once

#include <Arduino.h>

// === logic ===
#include "relay.hpp"
#include "tempSensor.hpp"

class TempRegulator : public Device {
 private:
  String name;
  String category = "TEMPERATURE";

  boolean enabled = false;
  TempSensor* tempSensor;

 public:
  void init();
  float get();
  String getName();
  String getCategory();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonDocument& obj);

  TempRegulator(String deviceName, TempSensor& _tempSensor);
};

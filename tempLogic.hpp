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

 public:
  void init();
  float get();
  String getName();
  String getCategory();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonObject& obj);

  TempRegulator(String deviceName);
};

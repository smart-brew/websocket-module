#pragma once

#include <Arduino.h>

// === logic ===
#include "pinEnabler.hpp"

class SimpleRelay : public Device {
 private:
  String name;
  String category = "SYSTEM";
  String instruction = "NONE";
  int status = DEVICE_WAITING;

  PinEnabler* pinEnabler;

 public:
  void init();
  void abort();
  float get();
  String getName();
  String getCategory();
  String getStatus();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonDocument& obj);

  SimpleRelay(String deviceName, String _category, String _instruction, PinEnabler& _pinEnabler);
  void updateStatus();
};

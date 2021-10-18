#pragma once

#include <Arduino.h>

// === logic ===
#include "relay.hpp"
#include "tempSensor.hpp"

class TempRegulator {
 private:
  bool enabled = false;
  float desiredTemperature;

  // when TEMP is around desired valued within this range, it is considered valid
  float VALID_MARGIN = 0.5;

  // === logic ===
  int sensorId = 0;
  void getHotter();
  void getCooler();

 public:
  void enable(bool enable);
  bool isEnabled();
  void setTemperature(float temperature);
  bool loop();
  TempRegulator(int sensorIdArg);
};

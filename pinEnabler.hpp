#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>  // download from: https://github.com/madhephaestus/ESP32Servo

#include "device.hpp"

class PinEnabler {
 private:
  int pin;
  bool isEnabled;

 public:
  void init();

  void enable();
  void disable();
  bool getStatus();

  PinEnabler(int pin);
};

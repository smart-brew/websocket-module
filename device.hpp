#pragma once

#include <ArduinoJson.h>

class Device {
 private:
  // device name
  String name;

  // device category
  String category;

 public:
  // name of device
  virtual String getName() = 0;
  // category of device
  virtual String getCategory() = 0;
};

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

  // initialize device
  virtual void init() = 0;

  // add all values that will be sent to server to 'obj'
  virtual void appendJsonValues(JsonObject &obj) = 0;

  // instruction execution
  virtual void executeFunction(JsonDocument &obj) = 0;
};

#pragma once

#include <ArduinoJson.h>

class Sensor {
 private:
  // device name
  String name;

 public:
  // initialize sensor
  virtual void init() = 0;

  // get measurable value
  virtual float get() = 0;

  // add all values that will be sent to server to 'obj'
  virtual void getJsonValues(JsonObject &obj) = 0;

  // name of device
  virtual String getName() = 0;
};

#pragma once

#include <ArduinoJson.h>

class Sensor {
 private:
  String name;

 public:
  virtual void init() = 0;
  virtual float get() = 0;
  virtual void getJsonValues(JsonObject &obj) = 0;
  virtual String getName() = 0;
};

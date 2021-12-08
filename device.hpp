#pragma once

#include <ArduinoJson.h>

#define DEVICE_WAITING 0
#define DEVICE_DONE 1
#define DEVICE_FAIL 2
#define DEVICE_IN_PROGRESS 3

static const char *DEVICE_STATUS[] = {"WAITING", "DONE", "FAIL", "IN_PROGRESS"};

class Device {
 private:
  // device name
  String name;

  // device category
  String category;

  // device status
  int status;

 public:
  // name of device
  virtual String getName() = 0;
  // category of device
  virtual String getCategory() = 0;
  // status of device
  virtual String getStatus() = 0;

  // initialize device
  virtual void init() = 0;

  // add all values that will be sent to server to 'obj'
  virtual void appendJsonValues(JsonObject &obj) = 0;

  // instruction execution
  virtual void executeFunction(JsonDocument &obj) = 0;

  // abort instruction
  virtual void abort() = 0;
};

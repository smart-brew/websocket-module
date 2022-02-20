#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>

#include "config/config.hpp"
#include "device.hpp"

extern bool RELAY_OPEN;

void startRelay();
void relayOpen();
void relayClose();

class RelayModule : public Device {
 private:
  String name;
  String category = "RELAY";
  int status = DEVICE_WAITING;

 public:
  void init();
  void abort();
  float get();
  String getName();
  String getCategory();
  String getStatus();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonDocument& obj);

  RelayModule(String sensorName);
  void updateStatus();
};

#pragma once

#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>  // to fix 'rtc_gpio_desc' error visit: https://githubmemory.com/repo/PaulStoffregen/OneWire/issues/100

#include "device.hpp"

class TempSensor : public Device {
 private:
  String name = "";
  String category = "TEMPERATURE";

  int sensorPin;

  OneWire oneWire;
  DallasTemperature dallasTempSensors;

 public:
  void init();
  float get();
  String getName();
  String getCategory();
  void appendJsonValues(JsonObject& obj);
  void executeFunction(JsonObject& obj);

  TempSensor(int pin);
};

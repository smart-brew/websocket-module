#pragma once

#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>  // to fix 'rtc_gpio_desc' error visit: https://githubmemory.com/repo/PaulStoffregen/OneWire/issues/100

#include "sensor.hpp"

class TempSensor : public Sensor {
 private:
  String name;

  int sensorPin;

  OneWire oneWire;
  DallasTemperature dallasTempSensors;

 public:
  void init();
  float get();
  String getName();
  void getJsonValues(JsonObject& obj);

  TempSensor(int pin, String sensorName);
};

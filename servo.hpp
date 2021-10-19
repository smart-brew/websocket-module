#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>  // download from: https://github.com/madhephaestus/ESP32Servo

#include "sensor.hpp"

class ServoMotor : public Sensor {
 private:
  String name;

  Servo servo;
  int servoPin;

 public:
  void init();
  float get();
  String getName();
  void getJsonValues(JsonObject &obj);

  ServoMotor(int pin, String sensorName);
  void write(int angle);
};

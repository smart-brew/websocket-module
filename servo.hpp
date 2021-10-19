#include <Arduino.h>
#include <ESP32Servo.h>  // download from: https://github.com/madhephaestus/ESP32Servo

#include "sensor.hpp"

class ServoMotor : public Sensor {
 private:
  Servo servo;

  int servoPin;

 public:
  float get();

  void write(int angle);

  
  void init();

  ServoMotor(int pin);
};

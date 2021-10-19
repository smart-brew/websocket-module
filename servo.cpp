#include "servo.hpp"

float ServoMotor::get() {
  return servo.read();
}

void ServoMotor::write(int angle) {
  servo.write(angle);
}

ServoMotor::ServoMotor(int pin) {
  servoPin = pin;
}

void ServoMotor::init() {
  servo.attach(servoPin);
  servo.write(90);
}
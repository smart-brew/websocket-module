#include "pinEnabler.hpp"

void PinEnabler::init() {
  Serial.printf("[pin enabler] init - %d\n", pin);
  pinMode(pin, OUTPUT);

  disable();
}

void PinEnabler::enable() {
  isEnabled = true;
  digitalWrite(pin, HIGH);
}

void PinEnabler::disable() {
  isEnabled = false;
  digitalWrite(pin, LOW);
}

bool PinEnabler::getStatus() {
  return isEnabled;
}

PinEnabler::PinEnabler(int _pin) {
  pin = _pin;
}

#include "tempLogic.hpp"

TempRegulator::TempRegulator(int sensorIdArg) {
  sensorId = sensorIdArg;
}

void TempRegulator::enable(bool enable) {
  enabled = enable;
}

bool TempRegulator::isEnabled() {
  return enabled;
}

void TempRegulator::setTemperature(float temperature) {
  desiredTemperature = temperature;
};

bool TempRegulator::loop() {
  if (!enabled) return false;

  float measuredTemp = getTemperature(sensorId);

  if (desiredTemperature > measuredTemp) {
    // needs to get hotter
    getHotter();
  } else if (desiredTemperature < measuredTemp) {
    // need to get cooler
    getCooler();
  }

  return abs(desiredTemperature - measuredTemp) < VALID_MARGIN;
}

// === logic ===
void TempRegulator::getCooler() {
  if (RELAY_OPEN) {
    relayClose();
  }
};

void TempRegulator::getHotter() {
  if (!RELAY_OPEN) {
    relayOpen();
  }
};

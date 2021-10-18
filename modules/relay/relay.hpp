#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>

#include "../../config/config.hpp"

extern bool RELAY_OPEN;

void startRelay();
void relayOpen();
void relayClose();

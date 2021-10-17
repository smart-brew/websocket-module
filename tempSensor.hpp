#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>  // fix 'rtc_gpio_desc' error https://githubmemory.com/repo/PaulStoffregen/OneWire/issues/100

#include "config.h"

void startTempSensors();

float getTemperature(int sensorId);
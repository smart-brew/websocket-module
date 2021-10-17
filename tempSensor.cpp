#include "tempSensor.hpp"

OneWire oneWire(SENSOR_TEMP_PIN);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);


void startTempSensors() {
    // start temperature sensors
    sensors.begin();
}

float getTemperature(int sensorId) {
    sensors.requestTemperatures(); 
    return sensors.getTempCByIndex(sensorId);
}
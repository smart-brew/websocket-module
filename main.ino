#include <Arduino.h>
#include <ArduinoJson.h>  // needs additional install

#include <vector>

#include "config/config.hpp"
#include "relay.hpp"
#include "sensor.hpp"
#include "servo.hpp"
// #include "tempLogic.hpp"
#include "tempSensor.hpp"
#include "webSocket.hpp"
#include "wifi.hpp"

// TempRegulator tempRegulator(0);

// create device objects here
ServoMotor servoMotor(27, "SERVO_1");
TempSensor tempSensor(SENSOR_TEMP_PIN, "TEMP_1");

static std::vector<std::reference_wrapper<Sensor>> sensors;

WiFiCls wifi(WIFI_SSID, WIFI_PWD);

void boot() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
}

void setup() {
  boot();

  // --- ADD ALL SENSORS TO ARRAY ---
  sensors.push_back(servoMotor);
  sensors.push_back(tempSensor);
  // --------------------------------

  for (Sensor& sensor : sensors) {
    sensor.init();
  }

  // start relay
  startRelay();

  // wifi login
  wifi.start();

  // start websocket client
  startWS();
}

unsigned long lastMessage = 0;

void loop() {
  webSocketLoop();

  uint64_t now = millis();

  if (now - lastMessage > 1000 && WS_CONNECTED) {
    lastMessage = now;

    // create json object
    DynamicJsonDocument data(1024);
    data["moduleId"] = MODULE_ID;
    data["status"] = MODULE_ID;

    // get all data from all sensors
    JsonArray values = data.createNestedArray("values");
    for (Sensor& sensor : sensors) {
      JsonObject vals = values.createNestedObject().createNestedObject(sensor.getName());
      sensor.getJsonValues(vals);
    }

    // send json using WS
    webSocketSendJson(data);
  }
}
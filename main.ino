#include <Arduino.h>
#include <ArduinoJson.h>  // needs additional install

#include <vector>

#include "H300.hpp"
#include "config/config.hpp"
#include "device.hpp"
#include "relay.hpp"
#include "servo.hpp"
#include "tempLogic.hpp"
#include "tempSensor.hpp"
#include "webSocket.hpp"
#include "wifi.hpp"

// TempRegulator tempRegulator(0);

// create device objects here
ServoMotor servoMotor(27, "SERVO_1");
TempSensor tempSensor(SENSOR_TEMP_PIN, "TEMP_1");
TempRegulator tempRegulator("TEMP_2");

// H300 h300("device-id", "mac-address", 2000, H300_RX, H300_TX, "MOTOR_1");

static std::vector<std::reference_wrapper<Device>> devices;

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
  devices.push_back(servoMotor);
  devices.push_back(tempSensor);
  devices.push_back(tempRegulator);
  // --------------------------------

  for (Device& device : devices) {
    device.init();
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

    // get all data from all devices
    for (Device& device : devices) {
      if (!data.containsKey(device.getCategory())) {
        // create array: eg. "TEMPERATURE: []"
        data.createNestedArray(device.getCategory());
      }

      // add data
      JsonObject deviceData = data[device.getCategory()].createNestedObject();
      deviceData["DEVICE"] = device.getName();
      device.appendJsonValues(deviceData);
    }

    // send json using WS
    webSocketSendJson(data);
  }
}
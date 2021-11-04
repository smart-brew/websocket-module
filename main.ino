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

// ---------- create device objects here ----------------------
ServoMotor servoMotor(27, "SERVO_1");
TempSensor tempSensor(SENSOR_TEMP_PIN);
TempRegulator tempRegulator("TEMP_2", tempSensor);

// H300 h300("device-id", "mac-address", 2000, H300_RX, H300_TX, "MOTOR_1");

static std::vector<std::reference_wrapper<Device>> devices;

WiFiCls wifi(WIFI_SSID, WIFI_PWD);

void boot();
void webSocketEvent(WStype_t type, uint8_t* payload, size_t length);

void setup() {
  boot();

  // --- ADD ALL SENSORS TO ARRAY ---
  devices.push_back(servoMotor);
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

  // websocket event handler
  webSocket.onEvent(webSocketEvent);
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

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  DynamicJsonDocument data(256);

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      WS_CONNECTED = false;
      break;

    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      WS_CONNECTED = true;

      data["moduleId"] = MODULE_ID;
      // send message to server when Connected
      webSocketSendJson(data);
      break;

    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);

      deserializeJson(data, payload);

      for (Device& device : devices) {
        device.executeFunction(data);
      }

      break;
  }
}
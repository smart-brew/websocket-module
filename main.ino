#include <Arduino.h>
#include <ArduinoJson.h>  // needs additional install

#include "config/config.hpp"
#include "relay.hpp"
#include "tempSensor.hpp"
#include "webSocket.hpp"
#include "wifi.hpp"

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

  // start relay
  startRelay();

  // start temperature sensors
  startTempSensors();
  Serial.println("[sensors] OK");

  // wifi login
  startWifi();
  Serial.println("[WIFI] WiFi connected");

  // start websocket client
  startWS();
}

unsigned long lastMessage = 0;
bool openRelay = false;

void loop() {
  webSocketLoop();

  uint64_t now = millis();

  if (now - lastMessage > 1000 && wsConnected) {
    lastMessage = now;

    // create json object
    DynamicJsonDocument json(512);
    JsonObject data = json.createNestedObject(MODULE_ID);

    // measure TEMPERATURE
    data["TEMP"] = getTemperature(0);

    if (openRelay) {
      relayClose();
      openRelay = false;
      data["RELAY"] = 0;
    } else {
      relayOpen();
      openRelay = true;
      data["RELAY"] = 1;
    }

    // send json using WS
    webSocketSendJson(json);
  }
}
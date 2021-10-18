#include <Arduino.h>
#include <ArduinoJson.h>  // needs additional install

#include "config/config.hpp"
#include "modules/relay/relay.hpp"
#include "modules/tempSensor/tempSensor.hpp"
#include "modules/webSocket/webSocket.hpp"
#include "modules/wifi/wifi.hpp"

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

void loop() {
  webSocketLoop();

  uint64_t now = millis();

  if (now - lastMessage > 1000 && WS_CONNECTED) {
    lastMessage = now;

    // create json object
    DynamicJsonDocument json(512);
    JsonObject data = json.createNestedObject(MODULE_ID);

    // measure TEMPERATURE
    data["TEMP"] = getTemperature(0);

    // get RELAY status
    data["RELAY"] = RELAY_OPEN;

    // send json using WS
    webSocketSendJson(json);
  }
}
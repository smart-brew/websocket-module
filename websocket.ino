#include <Arduino.h>

// built-in
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>

// needs install
#include <ArduinoJson.h>

#include "config.h"
#include "tempSensor.hpp"
#include "webSocket.hpp"


// wifi
WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  
  // start temperature sensors
  startTempSensors();
  Serial.println("[sensors] OK");

  // wifi login
  WiFiMulti.addAP(WIFI_SSID, WIFI_PWD);

  // wait to load wifi
  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("[WIFI] Retry wifi...");
    delay(1000);
  }
  Serial.println("[WIFI] WiFi connected");

  // start websocket client
  startWS();
}

unsigned long messageTimestamp = 0;

void loop() {
  webSocketLoop();

  uint64_t now = millis();
  
  if(now - messageTimestamp > 1000 && wsConnected) {
    messageTimestamp = now;

    // create json object
    DynamicJsonDocument json(512);
    JsonObject data = json.createNestedObject(MODULE_ID);
    
    // measure TEMPERATURE
    data["TEMP"] = getTemperature(0);
    
    // json -> string
    String output;
    serializeJson(json, output);
    
    webSocketSendTXT(output);
    Serial.printf("[WS] Sending: ");
    Serial.println(output);
  }
}

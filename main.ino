#include <Arduino.h>
#include <ArduinoJson.h>  // needs additional install

#include "config/config.hpp"
#include "relay.hpp"
#include "servo.hpp"
#include "tempLogic.hpp"
#include "tempSensor.hpp"
#include "webSocket.hpp"
#include "wifi.hpp"

TempRegulator tempRegulator(0);
ServoMotor servoMotor(27);

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

  // start servo
  servoMotor.init();

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

    // TEST - start temp regulation when 25 degrees or more
    if (!tempRegulator.isEnabled() && getTemperature(0) > 25) {
      tempRegulator.enable(true);
      tempRegulator.setTemperature(30);

      servoMotor.write(30);
    }

    data["TEMP_REGULATOR_ENABLED"] = tempRegulator.isEnabled();
    data["TEMP_REGULATOR_DONE"] = tempRegulator.loop();

    // get RELAY status
    data["RELAY"] = RELAY_OPEN;

    // measure SERVO_POSITION
    data["SERVO_POS"] = servoMotor.get();

    // send json using WS
    webSocketSendJson(json);
  }
}
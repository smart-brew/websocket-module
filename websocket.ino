#include <Arduino.h>

// built-in
#include <DallasTemperature.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>


// source https://github.com/Links2004/arduinoWebSockets
#include <WebSocketsClient.h>

// needs install
#include <OneWire.h> // fix 'rtc_gpio_desc' error https://githubmemory.com/repo/PaulStoffregen/OneWire/issues/100
#include <ArduinoJson.h>

#include "config.h"

// wifi
WiFiMulti WiFiMulti;

// web socket
WebSocketsClient webSocket;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(SENSOR_TEMP_PIN);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);


bool serverReady = false;

void hexdump(const void *mem, uint32_t len, uint8_t cols = 16) {
  const uint8_t* src = (const uint8_t*) mem;
  Serial.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
  for(uint32_t i = 0; i < len; i++) {
    if(i % cols == 0) {
      Serial.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
    }
    Serial.printf("%02X ", *src);
    src++;
  }
  Serial.printf("\n");
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      serverReady = false;
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      serverReady = true;

      // send message to server when Connected
      webSocket.sendTXT(MODULE_ID);
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);

      // send message to server
      // webSocket.sendTXT("message here");
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
    case WStype_ERROR:      
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
  }

}


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
  sensors.begin();
  Serial.println("[sensors] OK");

  // wifi login
  WiFiMulti.addAP(WIFI_SSID, WIFI_PWD);

  // wait to load wifi
  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.println("[WIFI] Retry wifi...");
    delay(1000);
  }
  Serial.println("[WIFI] WiFi connected");

  // WS server address, port and URL
  webSocket.begin(WS_HOST, WS_PORT, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // try every 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);

}

unsigned long messageTimestamp = 0;

void loop() {
  webSocket.loop();

  uint64_t now = millis();
  
  if(now - messageTimestamp > 1000 && serverReady) {
    messageTimestamp = now;

    // create json object
    DynamicJsonDocument json(512);
    JsonObject device_object = json.createNestedObject(MODULE_ID);
    
    // measure TEMPERATURE
    sensors.requestTemperatures(); 
    float temperatureC = sensors.getTempCByIndex(0);
    Serial.print(temperatureC);
    Serial.println("ºC");
    
    device_object["TEMP"] = temperatureC;
    
    // json -> string
    String output;
    serializeJson(json, output);
    
    webSocket.sendTXT(output);
    Serial.printf("[WS] Sending: ");
    Serial.println(output);
  }
}

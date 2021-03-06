#include <Arduino.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>  // source https://github.com/Links2004/arduinoWebSockets

#include "config/config.hpp"

extern WebSocketsClient webSocket;

extern bool WS_CONNECTED;

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);

void startWS();

void webSocketLoop();

void webSocketSendTXT(String output);

void webSocketSendJson(DynamicJsonDocument json);
#include <Arduino.h>

// source https://github.com/Links2004/arduinoWebSockets
#include <WebSocketsClient.h>

#include <ArduinoJson.h>

#include "config.h"

extern bool wsConnected;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);

void startWS();

void webSocketLoop();

void webSocketSendTXT(String output);
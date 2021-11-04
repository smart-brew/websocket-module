#include "webSocket.hpp"

// web socket
WebSocketsClient webSocket;

bool WS_CONNECTED = false;

void startWS() {
  // WS server address, port and URL
  webSocket.begin(WS_HOST, WS_PORT, "/");

  // try every 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);

  WS_CONNECTED = false;
}

void webSocketLoop() {
  webSocket.loop();
}

void webSocketSendTXT(String output) {
  webSocket.sendTXT(output);
}

void webSocketSendJson(DynamicJsonDocument json) {
  String output;
  serializeJson(json, output);

  webSocket.sendTXT(output);

  Serial.printf("[WS] Sending: ");
  Serial.println(output);
}
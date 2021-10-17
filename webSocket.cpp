#include "webSocket.hpp"


// web socket
WebSocketsClient webSocket;


bool wsConnected = false;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      wsConnected = false;
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      wsConnected = true;

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

void startWS() {
  // WS server address, port and URL
  webSocket.begin(WS_HOST, WS_PORT, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);

  // try every 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);

  wsConnected = false;
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
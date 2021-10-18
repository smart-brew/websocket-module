#include "relay.hpp"

bool RELAY_OPEN = false;

void startRelay() {
  Serial2.begin(9600, SERIAL_8N1, RELAY_RX, RELAY_TX);
}

void relayOpen() {
  // open: A0 01 00 A1
  Serial2.write("\xa0\x01");
  Serial2.write(0x00);  // null terminates a string so it has to be sent on its own
  Serial2.write(0xa1);

  RELAY_OPEN = true;
}
void relayClose() {
  // close: A0 01 01 A2
  Serial2.write("\xa0\x01\x01\xa2");

  RELAY_OPEN = false;
}

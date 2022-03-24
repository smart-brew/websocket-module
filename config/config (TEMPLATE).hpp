#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID "wifi"
#define WIFI_PWD "password"
#define MODULE_ID "module id"

#define WS_HOST "1.2.3.4"
#define WS_PORT 1234

#define SERIAL2_BAUD 19200

#define WS_SEND_INTERVAL 1000

// tested on: 4, 25
// not working: 32
#define SENSOR_TEMP_PIN 25

#define RELAY_TX 16
#define RELAY_RX 17

#define H300_TX 10
#define H300_RX 11

#endif  // CONFIG_H

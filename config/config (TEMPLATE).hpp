#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID "PETO-NB"
#define WIFI_PWD "wE3040-3"
// #define WIFI_SSID "rpiWifi"
// #define WIFI_PWD "tp062122"

// #define WS_HOST "10.20.1.1"
#define WS_HOST "192.168.100.248"

#define MODULE_ID 1
#define WS_PORT 8001

#define SERIAL2_BAUD 19200

#define WS_SEND_INTERVAL 1000

// tested on: 4, 25
// not working: 32
#define SENSOR_TEMP_PIN 25

#define RELAY_TX 16
#define RELAY_RX 17

// #define H300_TX 10
// #define H300_RX 11

#define MAX485_DE 5
#define MAX485_RE_NEG 18

#endif  // CONFIG_H
